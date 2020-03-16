module top ( input clk

           , output B0_C
           , output B0_LE0
           , output B0_LE1
           , output B0_S00_S09_D
           , output B0_S01_S10_D
           , output B0_S02_S11_D
           , output B0_S03_S12_D
           , output B0_S04_S13_D
           , output B0_S05_S14_D
           , output B0_S06_S15_D
           , output B0_S07_S16_D
           , output B0_S08_S17_D

           , output B1_C
           , output B1_LE0
           , output B1_LE1
           , output B1_S18_S27_D
           , output B1_S19_S28_D
           , output B1_S20_S29_D
           , output B1_S21_S30_D
           , output B1_S22_S31_D
           , output B1_S23_S32_D
           , output B1_S24_S33_D
           , output B1_S25_S34_D
           , output B1_S26_S35_D

           , output B2_C
           , output B2_LE0
           , output B2_LE1
           , output B2_S36_S45_D
           , output B2_S37_S46_D
           , output B2_S38_S47_D
           , output B2_S39_S48_D
           , output B2_S40_S49_D
           , output B2_S41_S50_D
           , output B2_S42_S51_D
           , output B2_S43_S52_D
           , output B2_S44_S53_D

           , output B3_C
           , output B3_LE0
           , output B3_LE1
           , output B3_S54_S63_D
           , output B3_S55_S64_D
           , output B3_S56_S65_D
           , output B3_S57_S66_D
           , output B3_S58_S67_D
           , output B3_S59_S68_D
           , output B3_S60_S69_D
           , output B3_S61_S70_D
           , output B3_S62_S71_D

           , input  spi1_mosi
           , output spi1_miso
           , input  spi1_sck

           , input  spi4_mosi
           , output spi4_miso
           , input  spi4_sck

           , input b0_b2_act
           , input b1_b3_act

           , input s00_act
           , input s01_act
           , input s02_act
           , input s03_act
           , input s04_act
           , input s05_act
           , input s06_act
           , input s07_act
           , input s08_act
           , input s09_act
           , input s10_act
           , input s11_act
           , input s12_act
           , input s13_act
           , input s14_act
           , input s15_act
           , input s16_act
           , input s17_act
           );

    /* Hardcode MISO; currently unused */
    assign spi1_miso = 1'b0;
    assign spi4_miso = 1'b0;

    /* Latch logic */
    wire first_half_act;
    wire second_half_act;
    assign first_half_act  = |{s00_act, s01_act, s02_act, s03_act, s04_act,
                               s05_act, s06_act, s07_act, s08_act};
    assign second_half_act = |{s09_act, s10_act, s11_act, s12_act, s13_act,
                               s14_act, s15_act, s16_act, s17_act};

    assign B0_LE0 = b0_b2_act && first_half_act;
    assign B0_LE1 = b0_b2_act && second_half_act;

    assign B1_LE0 = b1_b3_act && first_half_act;
    assign B1_LE1 = b1_b3_act && second_half_act;

    assign B2_LE0 = b0_b2_act && first_half_act;
    assign B2_LE1 = b0_b2_act && second_half_act;

    assign B3_LE0 = b1_b3_act && first_half_act;
    assign B3_LE1 = b1_b3_act && second_half_act;

    /* Clock de-muxing */
    assign B0_C  = b0_b2_act && spi1_sck;
    assign B1_C  = b1_b3_act && spi1_sck;

    assign B2_C  = b0_b2_act && spi4_sck;
    assign B3_C  = b1_b3_act && spi4_sck;

    /* Data de-muxing */
    assign B0_S00_S09_D = (s00_act || s09_act) && spi1_mosi;
    assign B0_S01_S10_D = (s01_act || s10_act) && spi1_mosi;
    assign B0_S02_S11_D = (s02_act || s11_act) && spi1_mosi;
    assign B0_S03_S12_D = (s03_act || s12_act) && spi1_mosi;
    assign B0_S04_S13_D = (s04_act || s13_act) && spi1_mosi;
    assign B0_S05_S14_D = (s05_act || s14_act) && spi1_mosi;
    assign B0_S06_S15_D = (s06_act || s15_act) && spi1_mosi;
    assign B0_S07_S16_D = (s07_act || s16_act) && spi1_mosi;
    assign B0_S08_S17_D = (s08_act || s17_act) && spi1_mosi;

    assign B1_S18_S27_D = (s00_act || s09_act) && spi1_mosi;
    assign B1_S19_S28_D = (s01_act || s10_act) && spi1_mosi;
    assign B1_S20_S29_D = (s02_act || s11_act) && spi1_mosi;
    assign B1_S21_S30_D = (s03_act || s12_act) && spi1_mosi;
    assign B1_S22_S31_D = (s04_act || s13_act) && spi1_mosi;
    assign B1_S23_S32_D = (s05_act || s14_act) && spi1_mosi;
    assign B1_S24_S33_D = (s06_act || s15_act) && spi1_mosi;
    assign B1_S25_S34_D = (s07_act || s16_act) && spi1_mosi;
    assign B1_S26_S35_D = (s08_act || s17_act) && spi1_mosi;

    assign B2_S36_S45_D = (s00_act || s09_act) && spi4_mosi;
    assign B2_S37_S46_D = (s01_act || s10_act) && spi4_mosi;
    assign B2_S38_S47_D = (s02_act || s11_act) && spi4_mosi;
    assign B2_S39_S48_D = (s03_act || s12_act) && spi4_mosi;
    assign B2_S40_S49_D = (s04_act || s13_act) && spi4_mosi;
    assign B2_S41_S50_D = (s05_act || s14_act) && spi4_mosi;
    assign B2_S42_S51_D = (s06_act || s15_act) && spi4_mosi;
    assign B2_S43_S52_D = (s07_act || s16_act) && spi4_mosi;
    assign B2_S44_S53_D = (s08_act || s17_act) && spi4_mosi;

    assign B3_S54_S63_D = (s00_act || s09_act) && spi4_mosi;
    assign B3_S55_S64_D = (s01_act || s10_act) && spi4_mosi;
    assign B3_S56_S65_D = (s02_act || s11_act) && spi4_mosi;
    assign B3_S57_S66_D = (s03_act || s12_act) && spi4_mosi;
    assign B3_S58_S67_D = (s04_act || s13_act) && spi4_mosi;
    assign B3_S59_S68_D = (s05_act || s14_act) && spi4_mosi;
    assign B3_S60_S69_D = (s06_act || s15_act) && spi4_mosi;
    assign B3_S61_S70_D = (s07_act || s16_act) && spi4_mosi;
    assign B3_S62_S71_D = (s08_act || s17_act) && spi4_mosi;

endmodule
