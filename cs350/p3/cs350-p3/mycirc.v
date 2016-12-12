module mycirc
(
    input wire i0
    input wire i1
    input wire i2
    output wire o0
    output wire o1
);

wire p0;

assign p0 = i1 & i2;
assign o0 = ~o1;
assign o1 = p0 | i0;

endmodule
