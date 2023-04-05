module zipdiv(clk_i, n0, n1, n16, n17, n18, n19);
  input clk_i;
  wire clk_i;
  input n0;
  input n1;
  wire n0;
  wire n1;
  wire n2;
  wire n3;
  wire n4;
  wire n5;
  wire n6;
  wire n7;
  wire n8;
  wire n9;
  wire n10;
  wire n11;
  wire n12;
  wire n13;
  wire n14;
  wire n15;
  wire n16;
  wire n17;
  wire n18;
  wire n19;
  output n16;
  output n17;
  output n18;
  output n19;
  sky130_fd_sc_hd__reg0 U0 (
    .CLK(clk_i),
    .D(n0),
    .Q(n2),
  );
  sky130_fd_sc_hd__reg0 U1 (
    .CLK(clk_i),
    .D(n0),
    .Q(n9),
  );
  sky130_fd_sc_hd__reg0 U2 (
    .CLK(clk_i),
    .D(n0),
    .Q(n11),
  );
  sky130_fd_sc_hd__reg1 U3 (
    .CLK(clk_i),
    .D(n1),
    .Q(n3),
  );
  sky130_fd_sc_hd__reg1 U4 (
    .CLK(clk_i),
    .D(n1),
    .Q(n10),
  );
  sky130_fd_sc_hd__reg1 U5 (
    .CLK(clk_i),
    .D(n1),
    .Q(n7),
  );
  sky130_fd_sc_hd__inv0 U6 (
    .A(n2),
    .X(n4)
  );
  sky130_fd_sc_hd__inv0 U7 (
    .A(n2),
    .X(n6)
  );
  sky130_fd_sc_hd__inv1 U8 (
    .A(n3),
    .X(n8)
  );
  sky130_fd_sc_hd__inv1 U9 (
    .A(n3),
    .X(n5)
  );
  sky130_fd_sc_hd__nand0 U10 (
    .A(n4),
    .B(n5),
    .X(n12)
  );
  sky130_fd_sc_hd__nand1 U11 (
    .A(n6),
    .B(n7),
    .X(n13)
  );
  sky130_fd_sc_hd__nand2 U12 (
    .A(n8),
    .B(n9),
    .X(n14)
  );
  sky130_fd_sc_hd__nand3 U13 (
    .A(n10),
    .B(n11),
    .X(n15)
  );
  sky130_fd_sc_hd__reg3 U14 (
    .CLK(clk_i),
    .D(n12),
    .Q(n16),
  );
  sky130_fd_sc_hd__reg4 U15 (
    .CLK(clk_i),
    .D(n13),
    .Q(n17),
  );
  sky130_fd_sc_hd__reg5 U16 (
    .CLK(clk_i),
    .D(n14),
    .Q(n18),
  );
  sky130_fd_sc_hd__reg6 U17 (
    .CLK(clk_i),
    .D(n15),
    .Q(n19),
  );
endmodule