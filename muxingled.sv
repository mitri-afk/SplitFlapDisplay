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

// Internal high-speed oscillator
HSOSC #(.CLKHF_DIV(2'b01))
hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));


// Counter
  always_ff @(posedge int_osc) begin
if(reset == 0)  counter <= 0;
else            counter <= counter + 1;
end

//sub-modules
selectSegment displayMaker(counter[16], display);
ledFSM0 fsmx(reset, counter[16], rowx, colxVal);
ledFSM3 fsmy(reset, counter[16], rowy, colyVal);
mux8 rowmux(display, rowx, rowy, row);
mux8 colxmux(display, colxVal, 8'b00000000, colx);
mux8 colymux(display, 8'b00000000, colyVal, coly);
//assign colx = 8'b11111111;
//assign coly = 8'b11111111;
//assign row = 8'b00000000;
endmodule

module ledFSM0 (input logic reset,
				 input logic clk,
				 output logic [7:0] row,
				 output logic [7:0] col);
 
/* FSM that says whether or not a key is pressed or not.
   If key pressed and other key also pressed after,
   will not acknowedlge new key press
*/

typedef enum logic [1:0] {S0, S1, S2} statetype;
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
S2: nextstate = S0;
default: nextstate = S0;
endcase

// output logic
assign col[0] = 0;
assign col[1] = (state == S2);
assign col[2] = (state == S1);
assign col[3] = (state == S0);
assign col[4] = (state == S0);
assign col[5] = (state == S1);
assign col[6] = (state == S2);
assign col[7] = 0;

assign row[0] = (state == S0 | state == S1 | state == S2);
assign row[1] = (state == S0 | state == S1);
assign row[2] = (state == S0 | state == S2);
assign row[3] = (state == S1 | state == S2);
assign row[4] = (state == S1 | state == S2);
assign row[5] = (state == S0 | state == S2);
assign row[6] = (state == S0 | state == S1);
assign row[7] = (state == S0 | state == S1 | state == S2);
endmodule


module ledFSM3(input logic reset,
				 input logic clk,
				 output logic [7:0] row,
				 output logic [7:0] col);
 
/* FSM that says whether or not a key is pressed or not.
   If key pressed and other key also pressed after,
   will not acknowedlge new key press
*/

typedef enum logic [1:0] {S0, S1, S2} statetype;
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
S2: nextstate = S0;
default: nextstate = S0;
endcase

// output logic
assign col[0] = 0;
assign col[1] = 0;
assign col[2] = 0;
assign col[3] = 0;
assign col[4] = (state == S2);
assign col[5] = (state == S1);
assign col[6] = (state == S0);
assign col[7] = (state == S0);


assign row[0] = (state == S0 | state == S1 | state == S2);
assign row[1] = (state == S0 | state == S1);
assign row[2] = (state == S0 | state == S2);
assign row[3] = (state == S1 | state == S2);
assign row[4] = (state == S1 | state == S2);
assign row[5] = (state == S0 | state == S2);
assign row[6] = (state == S0 | state == S1);
assign row[7] = (state == S0 | state == S1 | state == S2);
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
