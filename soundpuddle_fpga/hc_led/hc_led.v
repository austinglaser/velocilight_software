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

    input d00,
    input d01,
    input d02,
    input d03,
    input d04,
    input d05,
    input d06,
    input d07,
    input d08,
    input d09,
    input d10,
    input d11,
    input d12,
    input d13,
    input d14,
    input d15,

    input nbl0,
    input nbl1,
    input ne1,
    input ne2,
    input noe,
    input nwe
);

    reg [7:0] resetn_counter = 0;
    wire resetn = &resetn_counter;
    always @(posedge clk) begin
        if (!resetn) begin
            resetn_counter <= resetn_counter + 1;
        end
    end

    wire idle0;
    wire idle1;
    wire idle2;
    wire idle3;
    wire idle;
    assign idle = idle0 && idle1 && idle2 && idle3;

    wire go;

    wire [31:0] frame0;
    wire [31:0] frame1;

    control c (
        .clk(clk),
        .resetn(resetn),
        .go(go),

        .idle(idle),

        .frame0(frame0),
        .frame1(frame1)
    );

    led_bank bank0 (
        .clk(clk),
        .resetn(resetn),
        .go(go),

        .idle(idle0),

        .frame0(frame0),
        .frame1(frame0),
        .frame2(frame0),
        .frame3(frame0),
        .frame4(frame0),
        .frame5(frame0),
        .frame6(frame0),
        .frame7(frame0),
        .frame8(frame0),
        .frame9(frame1),
        .frame10(frame1),
        .frame11(frame1),
        .frame12(frame1),
        .frame13(frame1),
        .frame14(frame1),
        .frame15(frame1),
        .frame16(frame1),
        .frame17(frame1),

        .dclk(B0_C),
        .latch0(B0_LE0),
        .latch1(B0_LE1),
        .data({B0_S00_S09_D,
               B0_S01_S10_D,
               B0_S02_S11_D,
               B0_S03_S12_D,
               B0_S04_S13_D,
               B0_S05_S14_D,
               B0_S06_S15_D,
               B0_S07_S16_D,
               B0_S08_S17_D})
    );

    led_bank bank1 (
        .clk(clk),
        .resetn(resetn),
        .go(go),

        .idle(idle1),

        .frame0(frame0),
        .frame1(frame0),
        .frame2(frame0),
        .frame3(frame0),
        .frame4(frame0),
        .frame5(frame0),
        .frame6(frame0),
        .frame7(frame0),
        .frame8(frame0),
        .frame9(frame1),
        .frame10(frame1),
        .frame11(frame1),
        .frame12(frame1),
        .frame13(frame1),
        .frame14(frame1),
        .frame15(frame1),
        .frame16(frame1),
        .frame17(frame1),

        .dclk(B1_C),
        .latch0(B1_LE0),
        .latch1(B1_LE1),
        .data({B1_S18_S27_D,
               B1_S19_S28_D,
               B1_S20_S29_D,
               B1_S21_S30_D,
               B1_S22_S31_D,
               B1_S23_S32_D,
               B1_S24_S33_D,
               B1_S25_S34_D,
               B1_S26_S35_D})
    );

    led_bank bank2 (
        .clk(clk),
        .resetn(resetn),
        .go(go),

        .idle(idle2),

        .frame0(frame0),
        .frame1(frame0),
        .frame2(frame0),
        .frame3(frame0),
        .frame4(frame0),
        .frame5(frame0),
        .frame6(frame0),
        .frame7(frame0),
        .frame8(frame0),
        .frame9(frame1),
        .frame10(frame1),
        .frame11(frame1),
        .frame12(frame1),
        .frame13(frame1),
        .frame14(frame1),
        .frame15(frame1),
        .frame16(frame1),
        .frame17(frame1),

        .dclk(B2_C),
        .latch0(B2_LE0),
        .latch1(B2_LE1),
        .data({B2_S36_S45_D,
               B2_S37_S46_D,
               B2_S38_S47_D,
               B2_S39_S48_D,
               B2_S40_S49_D,
               B2_S41_S50_D,
               B2_S42_S51_D,
               B2_S43_S52_D,
               B2_S44_S53_D})
    );

    led_bank bank3 (
        .clk(clk),
        .resetn(resetn),
        .go(go),

        .idle(idle3),

        .frame0(frame0),
        .frame1(frame0),
        .frame2(frame0),
        .frame3(frame0),
        .frame4(frame0),
        .frame5(frame0),
        .frame6(frame0),
        .frame7(frame0),
        .frame8(frame0),
        .frame9(frame1),
        .frame10(frame1),
        .frame11(frame1),
        .frame12(frame1),
        .frame13(frame1),
        .frame14(frame1),
        .frame15(frame1),
        .frame16(frame1),
        .frame17(frame1),

        .dclk(B3_C),
        .latch0(B3_LE0),
        .latch1(B3_LE1),
        .data({B3_S54_S63_D,
               B3_S55_S64_D,
               B3_S56_S65_D,
               B3_S57_S66_D,
               B3_S58_S67_D,
               B3_S59_S68_D,
               B3_S60_S69_D,
               B3_S61_S70_D,
               B3_S62_S71_D})
    );

endmodule

module control #(
    parameter LEDS = 20
) (
    input clk,
    input resetn,

    input idle,

    output reg go,
    output reg [31:0] frame0,
    output reg [31:0] frame1
);

    parameter SSIZE  = 3;
    parameter SSTART = 3'b001;
    parameter SLED   = 3'b010;
    parameter SSTOP  = 3'b100;

    parameter FSTART = 'h00000000;
    parameter FSTOP  = 'hFFFFFFFF;
    parameter FRED   = 'hFF0000FF;
    parameter FGREEN = 'hFF00FF00;

    reg  [SSIZE-1:0] state;
    wire [SSIZE-1:0] next_state;
    reg  [$clog2(LEDS):0] led;

    assign next_state = next_state_function(state, led);

    function [SSIZE-1:0] next_state_function;
        input [SSIZE-1:0] state;
        input [$clog2(LEDS):0] led;
        case (state)
            SSTART: next_state_function = SLED;

            SLED: if (led == LEDS) begin
                next_state_function = SSTOP;
            end else begin
                next_state_function = SLED;
            end

            SSTOP: next_state_function = SSTART;

            default: next_state_function = SSTOP;
        endcase
    endfunction

    always @(posedge idle) begin
        if (!resetn) begin
            state <= SSTART;
        end else begin
            state <= next_state;
        end
    end

    always @(posedge clk) begin
        if (!resetn) begin
            go <= 0;
            frame0 <= 32'b0;
            frame1 <= 32'b0;
        end else if (idle) begin
            go <= 1;
            case (state)
                SSTART: begin
                    frame0 <= FSTART;
                    frame1 <= FSTART;
                end

                SLED: begin
                    frame0 <= FRED;
                    frame1 <= FGREEN;
                end

                SSTOP: begin
                    frame0 <= FSTOP;
                    frame1 <= FSTOP;
                end
            endcase
        end else begin
            go <= 0;
        end
    end

    always @(posedge idle) begin
        if (!resetn) begin
            led <= 0;
        end else if (state == SLED) begin
            led <= led + 1;
        end else if (state == SSTART) begin
            led <= 0;
        end
    end

endmodule
