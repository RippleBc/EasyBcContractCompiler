program helloworld;
var
		inta, intb, intc : integer;
begin
		intb := 10 + 20;
		intc := 20;
		inta := (intb + intc) + 3 * (intb + intc);
		writeln('inta = ', inta);
end.
