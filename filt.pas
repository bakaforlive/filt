program cliParams;

{ TODO: Expand features for check param
 e.g. make the 'binary' - turn letters to random binary digits;
 'unreadable' - makes the text gibberish }

const
	LOWER_UPPERCASE_DIFF = 32;

// Prints help documentation
procedure helpDocs;
begin
        writeln('CLI - a program-filter.', #10, 'Parameters', #10, 'seek - SEEK for a specified characters.', #10#9, 'digits', #10#9, 'letters', #10#9, 'spaces', #10#9, 'capital-letters', #10#9, 'lowercase-letters', #10#10, 'change - CHANGE the format.', #10#9, 'letters-lower - formats any capital letters to lower.', #10#9, 'letters-upper - vice versa. Formats any lowercase letters to uppercase.');
        halt(0)
end;

// 'seek param' functions
procedure seekDigits(var ch: char; var isPrint: boolean);
begin
	if (ch >= '0') and (ch <= '9') then
		isPrint := true
	else
		isPrint := false
end;

procedure seekLetters(var ch: char; var isPrint: boolean);
begin
	if (((ch >= 'a') and (ch <= 'z'))) or (((ch >= 'A') and (ch <= 'Z'))) then
		isPrint := true
	else
		isPrint := false
end;

procedure seekSpaces(var ch: char; var isPrint: boolean);
begin
	if (ord(ch) <= 32) then
		isPrint := true
	else
		isPrint := false
end;

procedure seekUppercase(var ch: char; var isPrint: boolean);
begin
	if ((ch >= 'A') and (ch <= 'Z')) then
		isPrint := true
	else
		isPrint := false

end;

procedure seekLowercase(var ch: char; var isPrint: boolean);
begin
	if ((ch >= 'a') and (ch <= 'z')) then
		isPrint := true
	else
		isPrint := false

end;

// 'change param' functions
procedure toUpperCase(var ch: char; var isChange: boolean; var elseChange: boolean); // toUpperCase(ch, isChange, elseChange)
begin
	if ch in ['a'..'z'] then
	begin
        	ch := chr(ord(ch) - LOWER_UPPERCASE_DIFF);
		isChange := true;
		elseChange := false
	end
	else 
	begin
		isChange := false;
		elseChange := true
	end;
end;

procedure toLowerCase(var ch: char; var isChange: boolean; var elseChange: boolean);
begin
	if ch in ['A'..'Z'] then
	begin
        	ch := chr(ord(ch) + LOWER_UPPERCASE_DIFF);
		isChange := true;
		elseChange := false
	end
	else
	begin
		isChange := false;
		elseChange := true
	end;
   
end;


// the 'checkers' - checks params and calling functions

// 2 level procedures
procedure checkSeekParams(var ch: char; var isPrint: boolean);
begin
        case ParamStr(2) of
                'digits':
                        seekDigits(ch, isPrint);
                'letters':
                        seekLetters(ch, isPrint);
                'spaces':
                        seekSpaces(ch, isPrint);
                'capital-letters':
                        seekUppercase(ch, isPrint);
                'lowercase-letters':
                        seekLowercase(ch, isPrint);
                else
                begin
                        writeln('[ERROR] Parameter ', ParamStr(2), ' not found! Type ''cli help'' for details.');
                        halt(1)
		end
	end;
end;

procedure checkChangeParams(var ch: char; var isChange: boolean; var elseChange: boolean);
begin
	case ParamStr(2) of
		'letters-upper':
			toUpperCase(ch, isChange, elseChange);
		'letters-lower':
			toLowerCase(ch, isChange, elseChange);
		else
                begin
                	writeln('[ERROR] Parameter ', ParamStr(2), ' not found! Type ''cli help'' for details.');
                        halt(1)
                end
	end;

end;

// 1 level procedure
procedure checkParams(var ch: char; var isPrint: boolean; var isChange: boolean; var elseChange: boolean);
begin
	case ParamStr(1) of
		'seek':
			checkSeekParams(ch, isPrint);
		'change':
			checkChangeParams(ch, isChange, elseChange);
		'help':
			helpDocs;
		else
		begin
			writeln('[ERROR] Parameter ', ParamStr(1), ' not found! Type ''./cli help'' for details.');
			halt(1)
		end
	end;
end;


// print total count of founded characters (seek param only)
procedure printFoundedCount(count: integer);
begin
	if count = 0 then
		exit;
	writeln(#10, 'Characters found: ', count)
end;

// main
var
	count: integer; // counts found characters (only for seek param)
	isPrint, isChange, elseChange: boolean; // checks - 'I need to print/change char?'
	
	ch: char;
begin
	count := 0;
	isPrint := false;
	isChange := false;
	elseChange := false;

	while not eof do
	begin
		read(ch);
		checkParams(ch, isPrint, isChange, elseChange);

		if isPrint then
		begin
			write(ch);
			inc(count)
		end;	

		if isChange then
			write(ch)
		else if elseChange then
			write(ch);
		
	end;
	
	printFoundedCount(count)
end.
