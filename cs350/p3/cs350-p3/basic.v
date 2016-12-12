module eq1
  (
    input wire i0
    output wire eq
  );

  wire p0;

  assign p0 = i0 | i0;
  assign eq = p0;

endmodule
