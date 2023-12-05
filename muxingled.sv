module top(input logic reset,
		   output logic [7:0] row,
		   output logic [7:0] colx, coly);
 
// Top most module that combines all sub-modules within
// to create the whole circuit, additional
//comments in each sub module

logic [1:0] display;
logic [7:0] rowx, rowy;
logic [7:0] colxVal, colyVal;
logic [32:0] counter;
logic [3:0] ledPos;
logic [63:0] xMatrix, yMatrix;

// Internal high-speed oscillator
HSOSC #(.CLKHF_DIV(2'b01))
hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));


// Counter
  always_ff @(posedge int_osc) begin
if(reset == 0)  counter <= 0;
else            counter <= counter + 1;
end

//sub-modules
selectSegment displayMaker(counter[14], display);
controllerFSM controller(reset, counter[22], ledPos);
sunDecoder decoder(ledPos, xMatrix, yMatrix);
mainLedFSM fsmx(reset, counter[14], 8'b11111111, xMatrix[63:56], xMatrix[55:48], xMatrix[47:40], xMatrix[39:32], xMatrix[31:24], xMatrix[23:16], xMatrix[15:8], xMatrix[7:0],  rowx, colxVal);
mainLedFSM fsmy(reset, counter[14], 8'b11111111, yMatrix[63:56], yMatrix[55:48], yMatrix[47:40], yMatrix[39:32], yMatrix[31:24], yMatrix[23:16], yMatrix[15:8], yMatrix[7:0], rowy, colyVal);
mux8 rowmux(display, rowx, rowy, row);
mux8 colxmux(display, colxVal, 8'b00000000, colx);
mux8 colymux(display, 8'b00000000, colyVal, coly);
//assign colx = 8'b11111111;
//assign coly = 8'b11111111;
//assign row = 8'b00000000;
endmodule

module controllerFSM(input logic reset, 
			  input logic clk,
			  output logic [3:0] ledPos);
			  
/* FSM that says whether or not a key is pressed or not.
   If key pressed and other key also pressed after,
   will not acknowedlge new key press
*/

typedef enum logic [3:0] {S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15} statetype;
statetype state, nextstate;


// state register
always_ff @(posedge clk)
if (reset == 0) state <= S0;
else state <= nextstate;

// next state logic
always_comb
case (state)	  
S0: nextstate = S1;
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
S15: nextstate = S0;
default: nextstate = S0;
endcase

// output logic
// output logic
assign ledPos[0] = (state == S1 | state == S3 | state == S5 | state == S7 | state == S9 | state == S11 | state == S13 | state == S15);
assign ledPos[1] = (state == S2 | state == S3 | state == S6 | state == S7 | state == S10 | state == S11 | state == S14 | state == S15);
assign ledPos[2] = (state == S4 | state == S5 | state == S6 | state == S7 | state == S12 | state == S13 | state == S14 | state == S15);
assign ledPos[3] = (state == S8 | state == S9 | state == S10 | state == S11 | state == S12 | state == S13 | state == S14 | state == S15);
endmodule


module mainLedFSM(input logic reset,
				 input logic clk,
				 input logic [7:0] colsOn,
				 input logic [7:0] col0_rowsOff,  
				 input logic [7:0] col1_rowsOff,  
				 input logic [7:0] col2_rowsOff,  
				 input logic [7:0] col3_rowsOff,  
				 input logic [7:0] col4_rowsOff,  
				 input logic [7:0] col5_rowsOff,  
				 input logic [7:0] col6_rowsOff,  
				 input logic [7:0] col7_rowsOff,  
				 output logic [7:0] row,
				 output logic [7:0] col);
 
/* FSM that says whether or not a key is pressed or not.
   If key pressed and other key also pressed after,
   will not acknowedlge new key press
*/

typedef enum logic [2:0] {S0, S1, S2, S3, S4, S5, S6, S7} statetype;
statetype state, nextstate;


// state register
always_ff @(posedge clk)
if (reset == 0) state <= S0;
else state <= nextstate;

// next state logic
always_comb
case (state)
S0: nextstate = S1;
S1: nextstate = S2;
S2: nextstate = S3;
S3: nextstate = S4;
S4: nextstate = S5;
S5: nextstate = S6;
S6: nextstate = S7;
S7: nextstate = S0;
default: nextstate = S0;
endcase

// output logic
assign col[0] = (colsOn[0] & state==S0);
assign col[1] = (colsOn[1] & state==S1);
assign col[2] = (colsOn[2] & state==S2);
assign col[3] = (colsOn[3] & state==S3);
assign col[4] = (colsOn[4] & state==S4);
assign col[5] = (colsOn[5] & state==S5);
assign col[6] = (colsOn[6] & state==S6);
assign col[7] = (colsOn[7] & state==S7);


assign row[0] = (col0_rowsOff[0] & state == S0 | col1_rowsOff[0] & state == S1 |  col2_rowsOff[0] & state == S2 | col3_rowsOff[0] & state == S3 | col4_rowsOff[0] & state == S4 | col5_rowsOff[0] & state == S5 | col6_rowsOff[0] & state == S6 | col7_rowsOff[0] & state == S7); 
assign row[1] = (col0_rowsOff[1] & state == S0 | col1_rowsOff[1] & state == S1 |  col2_rowsOff[1] & state == S2 | col3_rowsOff[1] & state == S3 | col4_rowsOff[1] & state == S4 | col5_rowsOff[1] & state == S5 | col6_rowsOff[1] & state == S6 | col7_rowsOff[1] & state == S7); 
assign row[2] = (col0_rowsOff[2] & state == S0 | col1_rowsOff[2] & state == S1 |  col2_rowsOff[2] & state == S2 | col3_rowsOff[2] & state == S3 | col4_rowsOff[2] & state == S4 | col5_rowsOff[2] & state == S5 | col6_rowsOff[2] & state == S6 | col7_rowsOff[2] & state == S7); 
assign row[3] = (col0_rowsOff[3] & state == S0 | col1_rowsOff[3] & state == S1 |  col2_rowsOff[3] & state == S2 | col3_rowsOff[3] & state == S3 | col4_rowsOff[3] & state == S4 | col5_rowsOff[3] & state == S5 | col6_rowsOff[3] & state == S6 | col7_rowsOff[3] & state == S7); 
assign row[4] = (col0_rowsOff[4] & state == S0 | col1_rowsOff[4] & state == S1 |  col2_rowsOff[4] & state == S2 | col3_rowsOff[4] & state == S3 | col4_rowsOff[4] & state == S4 | col5_rowsOff[4] & state == S5 | col6_rowsOff[4] & state == S6 | col7_rowsOff[4] & state == S7); 
assign row[5] = (col0_rowsOff[5] & state == S0 | col1_rowsOff[5] & state == S1 |  col2_rowsOff[5] & state == S2 | col3_rowsOff[5] & state == S3 | col4_rowsOff[5] & state == S4 | col5_rowsOff[5] & state == S5 | col6_rowsOff[5] & state == S6 | col7_rowsOff[5] & state == S7); 
assign row[6] = (col0_rowsOff[6] & state == S0 | col1_rowsOff[6] & state == S1 |  col2_rowsOff[6] & state == S2 | col3_rowsOff[6] & state == S3 | col4_rowsOff[6] & state == S4 | col5_rowsOff[6] & state == S5 | col6_rowsOff[6] & state == S6 | col7_rowsOff[6] & state == S7); 
assign row[7] = (col0_rowsOff[7] & state == S0 | col1_rowsOff[7] & state == S1 |  col2_rowsOff[7] & state == S2 | col3_rowsOff[7] & state == S3 | col4_rowsOff[7] & state == S4 | col5_rowsOff[7] & state == S5 | col6_rowsOff[7] & state == S6 | col7_rowsOff[7] & state == S7); 
endmodule

module selectSegment (input logic clk,
 output logic [1:0] display);

// Decides what 7-segment display should be on
// based on a clk signal, as it outputs a 2 bit
// signal, with the first bit representing whether
// or not the first digit should be on and the second
// bit  representing whether or not the second digit
// should be on

always_comb
case (clk)
// when clk low, only turn on second signal
1'b0: display = 2'b10;
// when clk high, only turn on first signal
1'b1: display = 2'b01;
default: display = 2'b10;
endcase
endmodule

module mux8 (input logic [1:0] display,
input logic [7:0] s0,
input logic [7:0] s1,
output logic [7:0] sC);

// is a mux that accepts two 4 bit inputs that
// represent the two dip switches and outputs
// one of them depending on a signal that
// represents whether or not the first
// 7-segment display should be on. If that
// signal is high, s0 will be chosen. If that
// signal is low, s1 will be chosen.

assign sC = display[0] ? s0:s1;
endmodule

module sunDecoder(input  logic [3:0] ledPos, 
	              output logic [63:0] xMatrix,
				  output logic [63:0] yMatrix);

always_comb
case(ledPos)
4'h0: xMatrix = 64'hFFBDE7C3C3E7BDFF;
4'h1: xMatrix = 64'hFF7BCF8787CF7BFF;
4'h2: xMatrix = 64'hFFF79F0F0F9FF7FF;
4'h3: xMatrix = 64'hFFEF3F1F1F3FEFFF;
4'h4: xMatrix = 64'hFFDF7F3F3F7FDFFF;
4'h5: xMatrix = 64'hFFBFFF7F7FFFBFFF;
4'h6: xMatrix = 64'hFF7FFFFFFFFF7FFF;
4'h7: xMatrix = 64'hFFFFFFFFFFFFFFFF;
4'h8: xMatrix = 64'hFFFFFFFFFFFFFFFF;
4'h9: xMatrix = 64'hFFFFFFFFFFFFFFFF;
4'hA: xMatrix = 64'hFFFEFFFFFFFFFEFF;
4'hB: xMatrix = 64'hFFFDFFFEFEFFFDFF;
4'hC: xMatrix = 64'hFFFBFEFCFCFEFBFF;
4'hD: xMatrix = 64'hFFF7FCF8F8FCF7FF;
4'hE: xMatrix = 64'hFFEFF9F0F0F9EFFF;
4'hF: xMatrix = 64'hFFDEF3E1E1F3DEFF;
default: xMatrix = 64'hFFFFFFFFFFFFFFFF;
endcase

always_comb
case(ledPos)
4'h0: yMatrix = 64'hFFFFFFFFFFFFFFFF;
4'h1: yMatrix = 64'hFFFFFFFFFFFFFFFF;
4'h2: yMatrix = 64'hFFFEFFFFFFFFFEFF;
4'h3: yMatrix = 64'hFFFDFFFEFEFFFDFF;
4'h4: yMatrix = 64'hFFFBFEFCFCFEFBFF;
4'h5: yMatrix = 64'hFFF7FCF8F8FCF7FF;
4'h6: yMatrix = 64'hFFEFF9F0F0F9EFFF;
4'h7: yMatrix = 64'hFFDEF3E1E1F3DEFF;
4'h8: yMatrix = 64'hFFBDE7C3C3E7BDFF;
4'h9: yMatrix = 64'hFF7BCF8787CF7BFF;
4'hA: yMatrix = 64'hFFF79F0F0F9FF7FF;
4'hB: yMatrix = 64'hFFEF3F1F1F3FEFFF;
4'hC: yMatrix = 64'hFFDF7F3F3F7FDFFF;
4'hD: yMatrix = 64'hFFBFFF7F7FFFBFFF;
4'hE: yMatrix = 64'hFF7FFFFFFFFF7FFF;
4'hF: yMatrix = 64'hFFFFFFFFFFFFFFFF;
default: yMatrix = 64'hFFFFFFFFFFFFFFFF;
endcase
endmodule
