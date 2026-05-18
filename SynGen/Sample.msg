TSynSampleSyn {first Identifier is considered to be the Class Name }
tk {second Identifier is considered to be the Identifier Prefix }

IdentStart '_', 'a'..'z', 'A'..'Z':: '_', '0'..'9', 'a'..'z', 'A'..'Z'::

TOKENTYPES

Identifier

Key

|><|

KEYS { all between KEYS and |><| is considered to be a keyword }

Hello

|><|

CHARS

'A'..'Z', 'a'..'z', '_':: Ident

BeginProc

fTokenID := IdentKind((fLine + Run));

inc(Run, fStringLen);

while Identifiers[fLine[Run]] do

Inc(Run);

EndProc

|><|