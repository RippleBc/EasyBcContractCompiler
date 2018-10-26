program helloworld;
	function testfunc(x,y:integer):integer;
		var
			k,sum : integer;
		begin
			sum := 1;
			for k:=2 to x div 2 do
			begin
			if x mod k = 0 then 
					begin
							writeln(980986);
							sum := sum + k;
					end;
			end;
			writeln(222222);
			writeln(x);
			writeln(y);
			writeln(sum);
			writeln(x + y);
			writeln(222222);
			testfunc := x + y; 
		end;
	begin
		testfunc(10, 1);
	end
.
