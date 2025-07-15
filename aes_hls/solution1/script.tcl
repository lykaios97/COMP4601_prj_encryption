############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project aes_hls
set_top aes_top
add_files AES_hls_cpp/HLS_top.cpp
add_files AES_hls_cpp/aes_cipher.cpp
add_files -tb AES_hls_cpp/aes_tb.cpp
open_solution "solution1"
set_part {xc7vx485tffg1157-1}
create_clock -period 10 -name default
#source "./aes_hls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
