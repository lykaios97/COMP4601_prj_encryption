// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module SubBytes (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        state_V_address0,
        state_V_ce0,
        state_V_we0,
        state_V_d0,
        state_V_q0
);

parameter    ap_ST_fsm_state1 = 5'd1;
parameter    ap_ST_fsm_state2 = 5'd2;
parameter    ap_ST_fsm_state3 = 5'd4;
parameter    ap_ST_fsm_state4 = 5'd8;
parameter    ap_ST_fsm_state5 = 5'd16;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
output  [3:0] state_V_address0;
output   state_V_ce0;
output   state_V_we0;
output  [7:0] state_V_d0;
input  [7:0] state_V_q0;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg[3:0] state_V_address0;
reg state_V_ce0;
reg state_V_we0;

(* fsm_encoding = "none" *) reg   [4:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
wire   [7:0] sbox_V_address0;
reg    sbox_V_ce0;
wire   [7:0] sbox_V_q0;
wire   [2:0] r_fu_75_p2;
reg   [2:0] r_reg_127;
wire    ap_CS_fsm_state2;
wire   [5:0] zext_ln80_fu_89_p1;
reg   [5:0] zext_ln80_reg_132;
wire   [0:0] icmp_ln79_fu_69_p2;
wire   [2:0] c_fu_99_p2;
reg   [2:0] c_reg_140;
wire    ap_CS_fsm_state3;
reg   [3:0] state_V_addr_reg_145;
wire   [0:0] icmp_ln80_fu_93_p2;
wire    ap_CS_fsm_state4;
reg   [2:0] r_0_reg_47;
reg   [2:0] c_0_reg_58;
wire    ap_CS_fsm_state5;
wire   [63:0] zext_ln544_2_fu_114_p1;
wire   [63:0] zext_ln544_fu_119_p1;
wire   [4:0] tmp_fu_81_p3;
wire   [5:0] zext_ln544_1_fu_105_p1;
wire   [5:0] add_ln544_fu_109_p2;
reg   [4:0] ap_NS_fsm;

// power-on initialization
initial begin
#0 ap_CS_fsm = 5'd1;
end

SubBytes_sbox_V #(
    .DataWidth( 8 ),
    .AddressRange( 256 ),
    .AddressWidth( 8 ))
sbox_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(sbox_V_address0),
    .ce0(sbox_V_ce0),
    .q0(sbox_V_q0)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln79_fu_69_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        c_0_reg_58 <= 3'd0;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        c_0_reg_58 <= c_reg_140;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln80_fu_93_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state3))) begin
        r_0_reg_47 <= r_reg_127;
    end else if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        r_0_reg_47 <= 3'd0;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        c_reg_140 <= c_fu_99_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        r_reg_127 <= r_fu_75_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln80_fu_93_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state3))) begin
        state_V_addr_reg_145 <= zext_ln544_2_fu_114_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln79_fu_69_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        zext_ln80_reg_132[4 : 2] <= zext_ln80_fu_89_p1[4 : 2];
    end
end

always @ (*) begin
    if ((((icmp_ln79_fu_69_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2)) | ((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln79_fu_69_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        sbox_V_ce0 = 1'b1;
    end else begin
        sbox_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        state_V_address0 = state_V_addr_reg_145;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        state_V_address0 = zext_ln544_2_fu_114_p1;
    end else begin
        state_V_address0 = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state3))) begin
        state_V_ce0 = 1'b1;
    end else begin
        state_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        state_V_we0 = 1'b1;
    end else begin
        state_V_we0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((icmp_ln79_fu_69_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((icmp_ln80_fu_93_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state3))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        ap_ST_fsm_state5 : begin
            ap_NS_fsm = ap_ST_fsm_state3;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln544_fu_109_p2 = (zext_ln80_reg_132 + zext_ln544_1_fu_105_p1);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign c_fu_99_p2 = (c_0_reg_58 + 3'd1);

assign icmp_ln79_fu_69_p2 = ((r_0_reg_47 == 3'd4) ? 1'b1 : 1'b0);

assign icmp_ln80_fu_93_p2 = ((c_0_reg_58 == 3'd4) ? 1'b1 : 1'b0);

assign r_fu_75_p2 = (r_0_reg_47 + 3'd1);

assign sbox_V_address0 = zext_ln544_fu_119_p1;

assign state_V_d0 = sbox_V_q0;

assign tmp_fu_81_p3 = {{r_0_reg_47}, {2'd0}};

assign zext_ln544_1_fu_105_p1 = c_0_reg_58;

assign zext_ln544_2_fu_114_p1 = add_ln544_fu_109_p2;

assign zext_ln544_fu_119_p1 = state_V_q0;

assign zext_ln80_fu_89_p1 = tmp_fu_81_p3;

always @ (posedge ap_clk) begin
    zext_ln80_reg_132[1:0] <= 2'b00;
    zext_ln80_reg_132[5] <= 1'b0;
end

endmodule //SubBytes
