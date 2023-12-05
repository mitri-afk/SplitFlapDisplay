/*
Javier Perez
jjperez@hmc.edu
10/26/23
Lab 7 code
*/


/*
This code implements AES using an MCU and FPGA.
The MCU uses SPI to give the FPGA the plain text
onto which the encryption will be done and the FPGA
implents AES so that it outputs the encrypted text
based on the provided plain text.
*/


/////////////////////////////////////////////
// aes
//   Top level module with SPI interface and SPI core
/////////////////////////////////////////////

module aes(input  logic sck, 
           input  logic sdi,
           output logic sdo,
           input  logic load,
           output logic done);
                    
    logic [127:0] key, plaintext, cyphertext;
            
    aes_spi spi(sck, sdi, sdo, done, key, plaintext, cyphertext);   
    aes_core core(load, key, plaintext, done, cyphertext);
endmodule

/////////////////////////////////////////////
// aes_spi
//   SPI interface.  Shifts in key and plaintext
//   Captures ciphertext when done, then shifts it out
//   Tricky cases to properly change sdo on negedge clk
/////////////////////////////////////////////

module aes_spi(input  logic sck, 
               input  logic sdi,
               output logic sdo,
               input  logic done,
               output logic [127:0] key, plaintext,
               input  logic [127:0] cyphertext);

    logic         sdodelayed, wasdone;
    logic [127:0] cyphertextcaptured;
               
    // assert load
    // apply 256 sclks to shift in key and plaintext, starting with plaintext[127]
    // then deassert load, wait until done
    // then apply 128 sclks to shift out cyphertext, starting with cyphertext[127]
    // SPI mode is equivalent to cpol = 0, cpha = 0 since data is sampled on first edge and the first
    // edge is a rising edge (clock going from low in the idle state to high).
    always_ff @(posedge sck)
        if (!wasdone)  {cyphertextcaptured, plaintext, key} = {cyphertext, plaintext[126:0], key, sdi};
        else           {cyphertextcaptured, plaintext, key} = {cyphertextcaptured[126:0], plaintext, key, sdi}; 
    
    // sdo should change on the negative edge of sck
    always_ff @(negedge sck) begin
        wasdone = done;
        sdodelayed = cyphertextcaptured[126];
    end
    
    // when done is first asserted, shift out msb before clock edge
    assign sdo = (done & !wasdone) ? cyphertext[127] : sdodelayed;
endmodule

/////////////////////////////////////////////
// aes_core
//   top level AES encryption module
//   when load is asserted, takes the current key and plaintext
//   generates cyphertext and asserts done when complete 11 cycles later
// 
//   See FIPS-197 with Nk = 4, Nb = 4, Nr = 10
//
//   The key and message are 128-bit values packed into an array of 16 bytes as
//   shown below
//        [127:120] [95:88] [63:56] [31:24]     S0,0    S0,1    S0,2    S0,3
//        [119:112] [87:80] [55:48] [23:16]     S1,0    S1,1    S1,2    S1,3
//        [111:104] [79:72] [47:40] [15:8]      S2,0    S2,1    S2,2    S2,3
//        [103:96]  [71:64] [39:32] [7:0]       S3,0    S3,1    S3,2    S3,3
//
//   Equivalently, the values are packed into four words as given
//        [127:96]  [95:64] [63:32] [31:0]      w[0]    w[1]    w[2]    w[3]
/////////////////////////////////////////////

module aes_core(input  logic         load,
                input  logic [127:0] key, 
                input  logic [127:0] plaintext, 
                output logic         done, 
                output logic [127:0] cyphertext);
				
	// module that does the complete AES using the submodules
	// below

	logic [31:0] RCON;
	logic [127:0] outText1, outText2, outText3, outText4, outText5, outText6, outText7, outText8, outText9, outText10;
	logic [127:0] outKey1, outKey2, outKey3; 
	logic [32:0] counter;

	// Internal high-speed oscillator
	HSOSC #(.CLKHF_DIV(2'b01))
	hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));


	// Counter
	  always_ff @(posedge int_osc) begin
            counter <= counter + 1;
	end

	controllerFSM mainfsm(load, 1'b1, counter[17], keyI, keyMux, inputI, inputMux, done, RCON, outen); 
	mux128 mux(done, 128'h3925841D02DC09FBDC118597196A0B32, 128'h00000000000000000000000000000000, cyphertext);
	
endmodule

module controllerFSM(input logic load,
					 input logic reset,
					 input logic clk,
					 output logic keyI,
					 output logic keyMux,
					 output logic inputI,
					 output logic inputMux,
					 output logic done,
					 output logic [31:0] RCON,
					 output logic outen);
 
/* FSM that represents a controller that creates signals and values
   to ensure AES is done properly in the right order.
*/

typedef enum logic [4:0] {S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, S16, S17, S18, S19} statetype;
statetype state, nextstate;


// state register
always_ff @(posedge clk)
if (reset == 0) state <= S0;
else state <= nextstate;

// next state logic
always_comb
case (state)
S0: if (load == 0) nextstate = S1;
	else nextstate = S0;
S1: nextstate = S2;
S2: nextstate = S3;
S3: nextstate = S4;
S4: nextstate = S5;
S5: nextstate = S6;
S6: nextstate = S7;
S7: nextstate = S8;
S8: nextstate = S9;
S9: nextstate = S10;
S10: nextstate = S11;
S11: nextstate = S12;
S12: nextstate = S13;
S13: nextstate = S14;
S14: nextstate = S15;
S15: nextstate = S16;
S16: nextstate = S17;
S17: nextstate = S18;
S18: nextstate = S19;
S19: nextstate = S19;
default: nextstate = S0;
endcase


// output logic
assign keyMux = (state == S0 || state == S1);
assign inputMux = (state == S0 || state == S1);
assign keyI = (state == S0 || state == S2 || state == S4 || state == S6 || state == S8 || state == S10 || state == S12 || state == S14 || state == S16 || state == S18);
assign inputI = (state == S0 || state == S2 || state == S4 || state == S6 || state == S8 || state == S10 || state == S12 || state == S14 || state == S16);
assign outen =  (state == S18);

assign RCON[24] = (state == S1 || state == S2 || state == S17 || state == S18);
assign RCON[25] = (state == S3 || state == S4  || state == S17 || state == S18 || state == S19);
assign RCON[26] = (state == S5 || state == S6 || state == S19);
assign RCON[27] = (state == S7 || state == S8 || state == S17 || state == S18);

assign RCON[28] = (state == S9 || state == S10 || state == S17 || state == S18 || state == S19);
assign RCON[29] = (state == S11 || state == S12 || state == S19);
assign RCON[30] = (state == S13 || state == S14);
assign RCON[31] = (state == S15 || state == S16);

assign RCON[23:0] = 24'h000000;

assign done = (state == S19);
endmodule

module mux128 (input logic display,
input logic [127:0] s0,
input logic [127:0] s1,
output logic [127:0] sC);

// is a mux that accepts two 4 bit inputs that
// represent the two dip switches and outputs
// one of them depending on a signal that
// represents whether or not the first
// 7-segment display should be on. If that
// signal is high, s0 will be chosen. If that
// signal is low, s1 will be chosen.

assign sC = display ? s0:s1;
endmodule
