module top(input logic reset,
		   input logic [1:0] signal,
		   output logic [7:0] row,
		   output logic [7:0] col);
 
// Top most module that combines all sub-modules within
// to create the whole circuit, additional
//comments in each sub module

// Top most module that combines all sub-modules within
// to create the whole circuit, additional
//comments in each sub module

logic [23:0] counter;
logic [7:0] r0, c0, r1, c1, r2, c2, r3, c3;

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
ledFSM2 FSM2(reset, counter[16], r2, c2);
ledFSM3 FSM3(reset, counter[16], r3, c3);
/*
mux2_8b colMux(signal[0], c1, c0, col); 
mux2_8b rowMux(signal[0], r1, r0, row); 
*/
mux4_8b colMux(c0, c1, c3, c2, signal, col); 
mux4_8b rowMux(r0, r1, r3, r2, signal, row); 
endmodule

/*
module mux2_8b (input signal,
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
*/
module mux4_8b(input logic [7:0] d0, d1, d2, d3,
			input logic [1:0] s,
			output logic [7:0] y);

assign y = s[1] ? (s[0] ? d3 : d2) : (s[0] ? d1 : d0);
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

module ledFSM2(input logic reset,
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
assign col[3] = (state == S2);
assign col[4] = (state == S1);
assign col[5] = (state == S0);
assign col[6] = (state == S0);
assign col[7] = (state == S1);


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
