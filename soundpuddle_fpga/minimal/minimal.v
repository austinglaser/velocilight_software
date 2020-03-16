module top (
    input clk,

    inout d00,

    input ne1,
    input noe,
    input nwe
);

reg latched;
wire d00_in;

SB_IO #(
    .PIN_TYPE(6'b 1010_01),
    .PULLUP(1'b 0)
) io (
    .PACKAGE_PIN(d00),
    .OUTPUT_ENABLE(!ne1 && !noe),
    .D_OUT_0(latched),
    .D_IN_0(d00_in)
);

always @(posedge nwe) begin
    if (!ne1) begin
        latched <= d00_in;
    end
end

endmodule
