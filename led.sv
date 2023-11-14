module top(input logic reset,
  input logic signal,
  output logic [7:0] row,
  output logic [7:0] col);
 
// Top most module that combines all sub-modules within
// to create the whole circuit, additional
//comments in each sub module

// Top most module that combines all sub-modules within
// to create the whole circuit, additional
//comments in each sub module

logic [23:0] counter;
logic [7:0] r0, c0, r1, c1;

// Internal high-speed oscillator
HSOSC #(.CLKHF_DIV(2'b01))
hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));


// Counter
  always_ff @(posedge int_osc) begin
if(reset == 0)  counter <= 0;
else            counter <= counter + 1;
  end

//sub-modules
ledFSM0 FSM0(reset, counter[16], r0, c0);
ledFSM1 FSM1(reset, counter[16], r1, c1);
mux8 colMux(signal, c0, c1, col); 
mux8 rowMux(signal, r0, r1, row); 
endmodule

/*
module ledDecoder(output logic [7:0] row,
 output logic [7:0] col);

assign row = 8'b11100111;
assign col = 8'b00011000;
endmodule
*/
module mux8 (input signal,
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

assign sC = signal ? s0:s1;
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

module ledFSM1(input logic reset,
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
assign col[2] = (state == S2);
assign col[3] = (state == S1);
assign col[4] = (state == S0);
assign col[5] = (state == S0);
assign col[6] = (state == S1);
assign col[7] = (state == S2);

assign row[0] = (state == S0 | state == S1 | state == S2);
assign row[1] = (state == S0 | state == S1);
assign row[2] = (state == S0 | state == S2);
assign row[3] = (state == S1 | state == S2);
assign row[4] = (state == S1 | state == S2);
assign row[5] = (state == S0 | state == S2);
assign row[6] = (state == S0 | state == S1);
assign row[7] = (state == S0 | state == S1 | state == S2);
endmodule
