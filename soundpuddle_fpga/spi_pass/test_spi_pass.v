reg spi1_mosi;
reg spi1_sck;

reg spi4_mosi;
reg spi4_sck;

reg b0_b2_act;
reg b1_b3_act;

reg s00_act;
reg s01_act;
reg s02_act;
reg s03_act;
reg s04_act;
reg s05_act;
reg s06_act;
reg s07_act;
reg s08_act;
reg s09_act;
reg s10_act;
reg s11_act;
reg s12_act;
reg s13_act;
reg s14_act;
reg s15_act;
reg s16_act;
reg s17_act;

wire B0_C;
wire B0_LE0;
wire B0_LE1;
wire B0_S00_S09_D;
wire B0_S01_S10_D;
wire B0_S02_S11_D;
wire B0_S03_S12_D;
wire B0_S04_S13_D;
wire B0_S05_S14_D;
wire B0_S06_S15_D;
wire B0_S07_S16_D;
wire B0_S08_S17_D;

wire B1_C;
wire B1_LE0;
wire B1_LE1;
wire B1_S18_S27_D;
wire B1_S19_S28_D;
wire B1_S20_S29_D;
wire B1_S21_S30_D;
wire B1_S22_S31_D;
wire B1_S23_S32_D;
wire B1_S24_S33_D;
wire B1_S25_S34_D;
wire B1_S26_S35_D;

wire B2_C;
wire B2_LE0;
wire B2_LE1;
wire B2_S36_S45_D;
wire B2_S37_S46_D;
wire B2_S38_S47_D;
wire B2_S39_S48_D;
wire B2_S40_S49_D;
wire B2_S41_S50_D;
wire B2_S42_S51_D;
wire B2_S43_S52_D;
wire B2_S44_S53_D;

wire B3_C;
wire B3_LE0;
wire B3_LE1;
wire B3_S54_S63_D;
wire B3_S55_S64_D;
wire B3_S56_S65_D;
wire B3_S57_S66_D;
wire B3_S58_S67_D;
wire B3_S59_S68_D;
wire B3_S60_S69_D;
wire B3_S61_S70_D;
wire B3_S62_S71_D;

top uut ( .B0_C(B0_C)
        , .B0_LE0(B0_LE0)
        , .B0_LE1(B0_LE1)
        , .B0_S00_S09_D(B0_S00_S09_D)
        , .B0_S01_S10_D(B0_S01_S10_D)
        , .B0_S02_S11_D(B0_S02_S11_D)
        , .B0_S03_S12_D(B0_S03_S12_D)
        , .B0_S04_S13_D(B0_S04_S13_D)
        , .B0_S05_S14_D(B0_S05_S14_D)
        , .B0_S06_S15_D(B0_S06_S15_D)
        , .B0_S07_S16_D(B0_S07_S16_D)
        , .B0_S08_S17_D(B0_S08_S17_D)

        , .B1_C(B1_C)
        , .B1_LE0(B1_LE0)
        , .B1_LE1(B1_LE1)
        , .B1_S18_S27_D(B1_S18_S27_D)
        , .B1_S19_S28_D(B1_S19_S28_D)
        , .B1_S20_S29_D(B1_S20_S29_D)
        , .B1_S21_S30_D(B1_S21_S30_D)
        , .B1_S22_S31_D(B1_S22_S31_D)
        , .B1_S23_S32_D(B1_S23_S32_D)
        , .B1_S24_S33_D(B1_S24_S33_D)
        , .B1_S25_S34_D(B1_S25_S34_D)
        , .B1_S26_S35_D(B1_S26_S35_D)

        , .B2_C(B2_C)
        , .B2_LE0(B2_LE0)
        , .B2_LE1(B2_LE1)
        , .B2_S36_S45_D(B2_S36_S45_D)
        , .B2_S37_S46_D(B2_S37_S46_D)
        , .B2_S38_S47_D(B2_S38_S47_D)
        , .B2_S39_S48_D(B2_S39_S48_D)
        , .B2_S40_S49_D(B2_S40_S49_D)
        , .B2_S41_S50_D(B2_S41_S50_D)
        , .B2_S42_S51_D(B2_S42_S51_D)
        , .B2_S43_S52_D(B2_S43_S52_D)
        , .B2_S44_S53_D(B2_S44_S53_D)

        , .B3_C(B3_C)
        , .B3_LE0(B3_LE0)
        , .B3_LE1(B3_LE1)
        , .B3_S54_S63_D(B3_S54_S63_D)
        , .B3_S55_S64_D(B3_S55_S64_D)
        , .B3_S56_S65_D(B3_S56_S65_D)
        , .B3_S57_S66_D(B3_S57_S66_D)
        , .B3_S58_S67_D(B3_S58_S67_D)
        , .B3_S59_S68_D(B3_S59_S68_D)
        , .B3_S60_S69_D(B3_S60_S69_D)
        , .B3_S61_S70_D(B3_S61_S70_D)
        , .B3_S62_S71_D(B3_S62_S71_D)

        , .spi1_mosi(spi1_mosi)
        , .spi1_sck(spi1_sck)

        , .spi4_mosi(spi4_mosi)
        , .spi4_sck(spi4_sck)

        , .b0_b2_act(b0_b2_act)
        , .b1_b3_act(b1_b3_act)

        , .s00_act(s00_act)
        , .s01_act(s01_act)
        , .s02_act(s02_act)
        , .s03_act(s03_act)
        , .s04_act(s04_act)
        , .s05_act(s05_act)
        , .s06_act(s06_act)
        , .s07_act(s07_act)
        , .s08_act(s08_act)
        , .s09_act(s09_act)
        , .s10_act(s10_act)
        , .s11_act(s11_act)
        , .s12_act(s12_act)
        , .s13_act(s13_act)
        , .s14_act(s14_act)
        , .s15_act(s15_act)
        , .s16_act(s16_act)
        , .s17_act(s17_act)
        );

integer bit;
reg [7:0] __byte0;
reg [7:0] __byte1;
`define WRITE_BYTES(_b0, _b1)                   \
    __byte0 = _b0;                              \
    __byte1 = _b1;                              \
    for (bit = 0; bit < 8; bit = bit + 1) begin \
        spi1_sck = 0;                           \
        spi4_sck = 0;                           \
        spi1_mosi = __byte0[bit];               \
        spi4_mosi = __byte1[bit];               \
                                                \
        #5;                                     \
                                                \
        spi1_sck = 1;                           \
        spi4_sck = 1;                           \
                                                \
        #5;                                     \
    end                                         \
    spi1_mosi = 0;                              \
    spi4_mosi = 0;                              \
    #5;


initial #0 begin
    spi1_mosi = 0;
    spi1_sck = 1;
    spi4_mosi = 0;
    spi4_sck = 1;
    b0_b2_act = 0;
    b1_b3_act = 0;
    s00_act = 0;
    s01_act = 0;
    s02_act = 0;
    s03_act = 0;
    s04_act = 0;
    s05_act = 0;
    s06_act = 0;
    s07_act = 0;
    s08_act = 0;
    s09_act = 0;
    s10_act = 0;
    s11_act = 0;
    s12_act = 0;
    s13_act = 0;
    s14_act = 0;
    s15_act = 0;
    s16_act = 0;
    s17_act = 0;

    #5;

    b0_b2_act = 1;
    b1_b3_act = 1;
    s00_act   = 1;
    s01_act   = 1;
    s02_act   = 1;
    s03_act   = 1;
    s04_act   = 1;
    s05_act   = 1;
    s06_act   = 1;
    s07_act   = 1;
    s08_act   = 1;
    s09_act   = 1;
    s10_act   = 1;
    s11_act   = 1;
    s12_act   = 1;
    s13_act   = 1;
    s14_act   = 1;
    s15_act   = 1;
    s16_act   = 1;
    s17_act   = 1;

    `WRITE_BYTES(8'hAA, 8'h55)

    b0_b2_act = 0;
    b1_b3_act = 0;
    s00_act   = 0;
    s01_act   = 0;
    s02_act   = 0;
    s03_act   = 0;
    s04_act   = 0;
    s05_act   = 0;
    s06_act   = 0;
    s07_act   = 0;
    s08_act   = 0;
    s09_act   = 0;
    s10_act   = 0;
    s11_act   = 0;
    s12_act   = 0;
    s13_act   = 0;
    s14_act   = 0;
    s15_act   = 0;
    s16_act   = 0;
    s17_act   = 0;

    b0_b2_act = 1;
    s00_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s00_act = 0;

    s01_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s01_act = 0;

    s02_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s02_act = 0;

    s03_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s03_act = 0;

    s04_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s04_act = 0;

    s05_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s05_act = 0;

    s06_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s06_act = 0;

    s07_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s07_act = 0;

    s08_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s08_act = 0;

    s09_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s09_act = 0;

    s10_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s10_act = 0;

    s11_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s11_act = 0;

    s12_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s12_act = 0;

    s13_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s13_act = 0;

    s14_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s14_act = 0;

    s15_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s15_act = 0;

    s16_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s16_act = 0;

    s17_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s17_act = 0;
    b0_b2_act = 0;

    b1_b3_act = 1;
    s00_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s00_act = 0;

    s01_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s01_act = 0;

    s02_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s02_act = 0;

    s03_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s03_act = 0;

    s04_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s04_act = 0;

    s05_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s05_act = 0;

    s06_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s06_act = 0;

    s07_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s07_act = 0;

    s08_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s08_act = 0;

    s09_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s09_act = 0;

    s10_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s10_act = 0;

    s11_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s11_act = 0;

    s12_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s12_act = 0;

    s13_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s13_act = 0;

    s14_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s14_act = 0;

    s15_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s15_act = 0;

    s16_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s16_act = 0;

    s17_act = 1;
    `WRITE_BYTES(8'hAA, 8'h55)
    s17_act = 0;
    b1_b3_act = 0;
end

reg B0_C0;
reg B0_C1;
reg B0_S00;
reg B0_S01;
reg B0_S02;
reg B0_S03;
reg B0_S04;
reg B0_S05;
reg B0_S06;
reg B0_S07;
reg B0_S08;
reg B0_S09;
reg B0_S10;
reg B0_S11;
reg B0_S12;
reg B0_S13;
reg B0_S14;
reg B0_S15;
reg B0_S16;
reg B0_S17;

always @(*) begin
    if (B0_LE0) begin
        B0_C0 <= B0_C;
        B0_S00 <= B0_S00_S09_D;
        B0_S01 <= B0_S01_S10_D;
        B0_S02 <= B0_S02_S11_D;
        B0_S03 <= B0_S03_S12_D;
        B0_S04 <= B0_S04_S13_D;
        B0_S05 <= B0_S05_S14_D;
        B0_S06 <= B0_S06_S15_D;
        B0_S07 <= B0_S07_S16_D;
        B0_S08 <= B0_S08_S17_D;
    end
    if (B0_LE1) begin
        B0_C1 <= B0_C;
        B0_S09 <= B0_S00_S09_D;
        B0_S10 <= B0_S01_S10_D;
        B0_S11 <= B0_S02_S11_D;
        B0_S12 <= B0_S03_S12_D;
        B0_S13 <= B0_S04_S13_D;
        B0_S14 <= B0_S05_S14_D;
        B0_S15 <= B0_S06_S15_D;
        B0_S16 <= B0_S07_S16_D;
        B0_S17 <= B0_S08_S17_D;
    end
end

reg B1_C0;
reg B1_C1;
reg B1_S18;
reg B1_S19;
reg B1_S20;
reg B1_S21;
reg B1_S22;
reg B1_S23;
reg B1_S24;
reg B1_S25;
reg B1_S26;
reg B1_S27;
reg B1_S28;
reg B1_S29;
reg B1_S30;
reg B1_S31;
reg B1_S32;
reg B1_S33;
reg B1_S34;
reg B1_S35;

always @(*) begin
    if (B1_LE0) begin
        B1_C0 <= B1_C;
        B1_S18 <= B1_S18_S27_D;
        B1_S19 <= B1_S19_S28_D;
        B1_S20 <= B1_S20_S29_D;
        B1_S21 <= B1_S21_S30_D;
        B1_S22 <= B1_S22_S31_D;
        B1_S23 <= B1_S23_S32_D;
        B1_S24 <= B1_S24_S33_D;
        B1_S25 <= B1_S25_S34_D;
        B1_S26 <= B1_S26_S35_D;
    end
    if (B1_LE1) begin
        B1_C1 <= B1_C;
        B1_S27 <= B1_S18_S27_D;
        B1_S28 <= B1_S19_S28_D;
        B1_S29 <= B1_S20_S29_D;
        B1_S30 <= B1_S21_S30_D;
        B1_S31 <= B1_S22_S31_D;
        B1_S32 <= B1_S23_S32_D;
        B1_S33 <= B1_S24_S33_D;
        B1_S34 <= B1_S25_S34_D;
        B1_S35 <= B1_S26_S35_D;
    end
end

reg B2_C0;
reg B2_C1;
reg B2_S36;
reg B2_S37;
reg B2_S38;
reg B2_S39;
reg B2_S40;
reg B2_S41;
reg B2_S42;
reg B2_S43;
reg B2_S44;
reg B2_S45;
reg B2_S46;
reg B2_S47;
reg B2_S48;
reg B2_S49;
reg B2_S50;
reg B2_S51;
reg B2_S52;
reg B2_S53;

always @(*) begin
    if (B2_LE0) begin
        B2_C0 <= B2_C;
        B2_S36 <= B2_S36_S45_D;
        B2_S37 <= B2_S37_S46_D;
        B2_S38 <= B2_S38_S47_D;
        B2_S39 <= B2_S39_S48_D;
        B2_S40 <= B2_S40_S49_D;
        B2_S41 <= B2_S41_S50_D;
        B2_S42 <= B2_S42_S51_D;
        B2_S43 <= B2_S43_S52_D;
        B2_S44 <= B2_S44_S53_D;
    end
    if (B2_LE1) begin
        B2_C1 <= B2_C;
        B2_S45 <= B2_S36_S45_D;
        B2_S46 <= B2_S37_S46_D;
        B2_S47 <= B2_S38_S47_D;
        B2_S48 <= B2_S39_S48_D;
        B2_S49 <= B2_S40_S49_D;
        B2_S50 <= B2_S41_S50_D;
        B2_S51 <= B2_S42_S51_D;
        B2_S52 <= B2_S43_S52_D;
        B2_S53 <= B2_S44_S53_D;
    end
end

reg B3_C0;
reg B3_C1;
reg B3_S54;
reg B3_S55;
reg B3_S56;
reg B3_S57;
reg B3_S58;
reg B3_S59;
reg B3_S60;
reg B3_S61;
reg B3_S62;
reg B3_S63;
reg B3_S64;
reg B3_S65;
reg B3_S66;
reg B3_S67;
reg B3_S68;
reg B3_S69;
reg B3_S70;
reg B3_S71;

always @(*) begin
    if (B3_LE0) begin
        B3_C0 <= B3_C;
        B3_S54 <= B3_S54_S63_D;
        B3_S55 <= B3_S55_S64_D;
        B3_S56 <= B3_S56_S65_D;
        B3_S57 <= B3_S57_S66_D;
        B3_S58 <= B3_S58_S67_D;
        B3_S59 <= B3_S59_S68_D;
        B3_S60 <= B3_S60_S69_D;
        B3_S61 <= B3_S61_S70_D;
        B3_S62 <= B3_S62_S71_D;
    end
    if (B2_LE1) begin
        B3_C1 <= B3_C;
        B3_S63 <= B3_S54_S63_D;
        B3_S64 <= B3_S55_S64_D;
        B3_S65 <= B3_S56_S65_D;
        B3_S66 <= B3_S57_S66_D;
        B3_S67 <= B3_S58_S67_D;
        B3_S68 <= B3_S59_S68_D;
        B3_S69 <= B3_S60_S69_D;
        B3_S70 <= B3_S61_S70_D;
        B3_S71 <= B3_S62_S71_D;
    end
end

