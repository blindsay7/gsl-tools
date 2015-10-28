%option noinput
%option nounput

%{
#include "columns.h"
%}

number [-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?

%%

{number} {
	yylval.val = strtod(yytext, (char **) NULL);
	return NUMBER;
}

\n return *yytext;


 /* [ ]?[\t,:][ ]?|[ ]+ {
	if (!haveSeparator)
		yylval.sep = find_sep( yytext );

	return SEP;
 } */
[ \t]+ /* ignore whitespace */

%%
