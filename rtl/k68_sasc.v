`include "k68_defines.v"


module k68_sasc (/*AUTOARG*/
   // Outputs
   tx_o, rts_o, dat_o, 
   // Inputs
   clk_i, rst_i, cts_i, rx_i, add_i, dat_i, cs_i, we_i
   ) ;

   // Set the default baud rate for the SASC
   parameter div0 = `k68_div0;
   parameter div1 = `k68_div1;
      
   input clk_i,rst_i;

   // IO
   output tx_o, rts_o;
   input  cts_i, rx_i;

   // Mem
   input [15:0] add_i;
   input [7:0] dat_i;
   input       cs_i, we_i;
   output [7:0] dat_o;
   reg    [7:0] dat_o;
   

   wire [7:0] 	dout;
   
   wire 	empty_o,full_o,sio_ce,sio_ce_x4;
   wire 	nrst;
   reg  [7:0] 	brg0, brg1;
   wire 	we, re;
   wire 	we_dat, re_dat;
   
   assign 	we = cs_i &  we_i;
   assign 	re = cs_i & !we_i;

   assign 	we_dat = we && add_i==`k68_UART_ADR_DATA;
   assign 	re_dat = re && add_i==`k68_UART_ADR_DATA;

   assign 	nrst = ~rst_i;

   always @(posedge clk_i or negedge nrst) begin
	if (!nrst) begin
	  brg0 <= div0;
	  brg1 <= div1;
	end else if (we && add_i==`k68_UART_ADR_BRG0) begin
	  brg0 <= dat_i;
	end else if (we && add_i==`k68_UART_ADR_BRG1) begin
	  brg1 <= dat_i;
	end
   end

   always @(posedge clk_i) begin
	case (add_i)
	  `k68_UART_ADR_DATA:   dat_o <= dout;
	  `k68_UART_ADR_STATUS: dat_o <= {6'b000000, full_o, empty_o};
	  `k68_UART_ADR_BRG0:   dat_o <= brg0;
	  `k68_UART_ADR_BRG1:   dat_o <= brg1;
	  default:              dat_o <= 8'h00;
	endcase
   end

 
   sasc_top sasc_top0(
		      .rxd_i(rx_i),
		      .txd_o(tx_o),
		      .cts_i(cts_i),
		      .rts_o(rts_o),
		      
		      .sio_ce(sio_ce),
		      .sio_ce_x4(sio_ce_x4),
		      
		      .din_i(dat_i),
		      .dout_o(dout),
		      
		      .re_i(re_dat),
		      .we_i(we_dat),
		      
		      .full_o(full_o),
		      .empty_o(empty_o),
		      
		      .clk(clk_i),.rst(nrst)
		      );
   
   sasc_brg sasc_brg0(
		      .sio_ce(sio_ce),
		      .sio_ce_x4(sio_ce_x4),
		      .div0(brg0),
		      .div1(brg1),
		      .clk(clk_i), .rst(nrst)
		      );
   
   
endmodule // k68_sasc
