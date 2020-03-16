module top (
    input clk,

    output B0_C,
    output B0_LE0,
    output B0_LE1,
    output B0_S00_S09_D,
    output B0_S01_S10_D,
    output B0_S02_S11_D,
    output B0_S03_S12_D,
    output B0_S04_S13_D,
    output B0_S05_S14_D,
    output B0_S06_S15_D,
    output B0_S07_S16_D,
    output B0_S08_S17_D,

    output B1_C,
    output B1_LE0,
    output B1_LE1,
    output B1_S18_S27_D,
    output B1_S19_S28_D,
    output B1_S20_S29_D,
    output B1_S21_S30_D,
    output B1_S22_S31_D,
    output B1_S23_S32_D,
    output B1_S24_S33_D,
    output B1_S25_S34_D,
    output B1_S26_S35_D,

    output B2_C,
    output B2_LE0,
    output B2_LE1,
    output B2_S36_S45_D,
    output B2_S37_S46_D,
    output B2_S38_S47_D,
    output B2_S39_S48_D,
    output B2_S40_S49_D,
    output B2_S41_S50_D,
    output B2_S42_S51_D,
    output B2_S43_S52_D,
    output B2_S44_S53_D,

    output B3_C,
    output B3_LE0,
    output B3_LE1,
    output B3_S54_S63_D,
    output B3_S55_S64_D,
    output B3_S56_S65_D,
    output B3_S57_S66_D,
    output B3_S58_S67_D,
    output B3_S59_S68_D,
    output B3_S60_S69_D,
    output B3_S61_S70_D,
    output B3_S62_S71_D,

    input a00,
    input a01,
    input a02,
    input a03,
    input a04,
    input a05,
    input a06,
    input a07,
    input a08,
    input a09,
    input a10,
    input a11,
    input a12,
    input a13,
    input a14,
    input a15,
    input a16,
    input a17,
    input a18,
    input a19,

    inout d00,
    inout d01,
    inout d02,
    inout d03,
    inout d04,
    inout d05,
    inout d06,
    inout d07,
    inout d08,
    inout d09,
    inout d10,
    inout d11,
    inout d12,
    inout d13,
    inout d14,
    inout d15,

    input nbl0,
    input nbl1,
    input ne1,
    input ne2,
    input noe,
    input nwe
);

// POR
reg [7:0] resetn_counter = 0;
wire resetn = &resetn_counter;
always @(posedge clk) begin
    if (!resetn) begin
        resetn_counter <= resetn_counter + 1;
    end
end

// Address and data busses
wire [19:0] addr;
wire [15:0] data_in;
reg  [15:0] data_out;

assign addr = { a19, a18, a17, a16, a15, a14, a13, a12, a11, a10
              , a09, a08, a07, a06, a05, a04, a03, a02, a01, a00
              };

// Register File
reg [15:0] stat;
reg [15:0] ctrl;
reg [15:0] data;

wire oe;
assign oe = !ne2 && !noe;

SB_IO #(
    .PIN_TYPE(6'b 1010_01),
    .PULLUP(1'b0)
) data_io [15:0] (
    .PACKAGE_PIN({ d15, d14, d13, d12, d11, d10, d09, d08
                 , d07, d06, d05, d04, d03, d02, d01, d00
                 }),
    .OUTPUT_ENABLE(oe),
    .D_OUT_0(data_out),
    .D_IN_0(data_in)
);

reg access;

always @(posedge clk) begin
    if (!resetn) begin
        stat <= 16'h0;
        ctrl <= 16'h0;
        data <= 16'h0;
        access <= 0;
    end else begin
        if (access) begin
            if (ne2) access <= 0;
        end else if (!ne2) begin
            (* parallel_case *)
            case (addr)
                /* STAT */
                20'h00000: begin
                    if (!noe) begin
                        access <= 1;
                        data_out <= stat;
                    end else if (!nwe) begin
                        access <= 1;
                        stat <= data_in;
                    end
                end

                /* CTRL */
                20'h00001: begin
                    if (!noe) begin
                        access <= 1;
                        data_out <= ctrl;
                    end else if (!nwe) begin
                        access <= 1;
                        ctrl <= data_in;
                    end
                end

                /* DATA */
                20'h00002: begin
                    if (!noe) begin
                        access <= 1;
                        data_out <= data;
                    end else if (!nwe) begin
                        access <= 1;
                        data <= data_in;
                    end
                end
            endcase
        end
    end
end

endmodule
