module add4(cy_in,x,y,sum,cy_out);
input [0:3]x;
input cy_in;
input [0:3]y;
output [0:3]sum;
output cy_out;
wire c0,c1,c2;
add f1(cy_in,x[3],y[3],c0,sum[3]);
add f2(c0,x[2],y[2],c1,sum[2]);
add f3(c1,x[1],y[1],c2,sum[1]);
add f4(c2,x[0],y[0],cy_out,sum[0]);
endmodule

module add(cy_in,x,y,cy_out,sum);
input cy_in,x,y;
output cy_out,sum;
xor x1(sum,cy_in,x,y);
assign cy_out=((x&y)|(y&cy_in)|(cy_in&x));
endmodule

module array_multiplier(a,b,c);
input [2:0]a;
input [3:0]b;
output [6:0]c;
wire [3:0]x;
wire [3:0]y;
wire [3:0]z;
wire [3:0]x_1;
wire [3:0]y_1;
reg in_1=0,in_2=0;
wire c_out;
and g1(c[0],b[0],a[0]);
assign x[3]=0;
assign x[2]=a[0]&b[3];
assign x[1]=a[0]&b[2];
assign x[0]=a[0]&b[1];
assign y={a[1]&b[3],a[1]&b[2],a[1]&b[1],a[1]&b[0]};
add4 a1(in_1,x,y,z,c_out);
assign c[1]=z[0];
assign x_1={c_out,z[3:1]};
assign y_1={a[2]&b[3],a[2]&b[2],a[2]&b[1],a[2]&b[0]};
add4 a2(in_2,x_1,y_1,c[5:2],c[6]);
endmodule

module test_multiplier;
reg [0:2]a;
reg [0:3]b;
wire [0:6]c;
array_multiplier A1(a,b,c);
	initial 
		begin
			$display("\t\ttime\ta\tb\tc");
			$monitor($time,"\t%b\t%b\t%b",a,b,c);
			#10 a=010;b=1010;
			#10 a=000;b=1111;
			#10 a=001;b=0111;
			#10 $finish;
		end
endmodule