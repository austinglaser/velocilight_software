module led_bank #(
    parameter integer FRAME_LENGTH = 32
) (
    input clk,
    input resetn,
    input go,

    input [FRAME_LENGTH-1:0] frame0,
    input [FRAME_LENGTH-1:0] frame1,
    input [FRAME_LENGTH-1:0] frame2,
    input [FRAME_LENGTH-1:0] frame3,
    input [FRAME_LENGTH-1:0] frame4,
    input [FRAME_LENGTH-1:0] frame5,
    input [FRAME_LENGTH-1:0] frame6,
    input [FRAME_LENGTH-1:0] frame7,
    input [FRAME_LENGTH-1:0] frame8,
    input [FRAME_LENGTH-1:0] frame9,
    input [FRAME_LENGTH-1:0] frame10,
    input [FRAME_LENGTH-1:0] frame11,
    input [FRAME_LENGTH-1:0] frame12,
    input [FRAME_LENGTH-1:0] frame13,
    input [FRAME_LENGTH-1:0] frame14,
    input [FRAME_LENGTH-1:0] frame15,
    input [FRAME_LENGTH-1:0] frame16,
    input [FRAME_LENGTH-1:0] frame17,

    output reg dclk,
    output reg latch0,
    output reg latch1,
    output reg [8:0] data,
    output idle
);
    /* State enumeration */
    parameter SSIZE   = 9;
    parameter SIDLE   = 9'b000000001;
    parameter SB0     = 9'b000000010;
    parameter SL0     = 9'b000000100;
    parameter SC0     = 9'b000001000;
    parameter SD0     = 9'b000010000;
    parameter SB1     = 9'b000100000;
    parameter SL1     = 9'b001000000;
    parameter SC1     = 9'b010000000;
    parameter SD1     = 9'b100000000;

    /* Local values */
    reg  [SSIZE-1:0] state;
    wire [SSIZE-1:0] next_state;
    reg [$clog2(FRAME_LENGTH):0] bit;

    /* Idle signal */
    assign idle = (state == SIDLE);

    /* Next state logic */
    assign next_state = next_state_function(state, bit, go);

    function [SSIZE-1:0] next_state_function;
        input [SSIZE-1:0] state;
        input [$clog2(FRAME_LENGTH):0] bit;
        input go;
        case (state)
            SIDLE: if (go == 1'b1) begin
                next_state_function = SB0;
            end else begin
                next_state_function = SIDLE;
            end

            SB0: next_state_function = SL0;

            SL0: next_state_function = SC0;

            SC0: next_state_function = SD0;

            SD0: next_state_function = SB1;

            SB1: next_state_function = SL1;

            SL1: next_state_function = SC1;

            SC1: next_state_function = SD1;

            SD1: if (bit == 0) begin
                next_state_function = SIDLE;
            end else begin
                next_state_function = SB0;
            end

            default: next_state_function = SIDLE;
        endcase
    endfunction

    always @(posedge clk) begin
        if (!resetn) begin
            state <= SIDLE;
        end else begin
            state <= next_state;
        end
    end

    always @(posedge clk) begin
        if (!resetn) begin
            dclk   <= 1;
            latch0 <= 1;
            latch1 <= 1;
            data   <= 9'b0;

            bit    <= FRAME_LENGTH;
        end else begin
            case (state)
                SIDLE: begin
                    data <= 9'b0;
                    dclk <= 1;
                    latch0 <= 0;
                    latch1 <= 0;
                    bit <= FRAME_LENGTH;
                end

                SB0: begin
                    data <= {frame0[bit - 1],
                             frame1[bit - 1],
                             frame2[bit - 1],
                             frame3[bit - 1],
                             frame4[bit - 1],
                             frame5[bit - 1],
                             frame6[bit - 1],
                             frame7[bit - 1],
                             frame8[bit - 1]};
                    dclk <= 0;
                end

                SL0: begin
                    latch0 <= 1;
                end

                SC0: begin
                    dclk <= 1;
                end

                SD0: begin
                    latch0 <= 0;
                end

                SB1: begin
                    data <= {frame9[bit - 1],
                             frame10[bit - 1],
                             frame11[bit - 1],
                             frame12[bit - 1],
                             frame13[bit - 1],
                             frame14[bit - 1],
                             frame15[bit - 1],
                             frame16[bit - 1],
                             frame17[bit - 1]};
                    dclk <= 0;
                    bit <=  bit - 1;
                end

                SL1: begin
                    latch1 <= 1;
                end

                SC1: begin
                    dclk <= 1;
                end

                SD1: begin
                    latch1 <= 0;
                end
            endcase
        end
    end

endmodule
