/*
 * Grammar for deck descriptions.
 */

grammar deckDescription;

deck 
    : IDNAME COLON idData
    | orderedIdName COLON idData
    | BASE64RLEMINUSNAME COLON base64RLEMinusData
    | orderedBase64RLEMinusName COLON base64RLEMinusData
    | MISSIONIDNAME COLON missionId
    | RAIDIDNAME COLON raidId
    | QUESTIDNAME COLON questId
    | MULTINAME COLON multiDeckData    
    ;

multiDeckData
    : multiDeckEntry (SEMICOLON multiDeckEntry)* SEMICOLON?
    ;      
    
multiDeckEntry
    : (RBRACE deck RBRACE | deck) (ASSIGNCARDINALITY deckCardinality )?
    ;

idData
    : NUMBER (COMMA NUMBER)*
    ;

missionId
    : NUMBER
    ;

questId
    : NUMBER
    ;

raidId
    : NUMBER
    ;

deckCardinality
    : NUMBER
    ;

base64RLEMinusData
    : BASE64RLEMINUSDATA
    ;

orderedIdName
    : ORDEREDNAME UNDERSCORE IDNAME
    | IDNAME UNDERSCORE ORDEREDNAME
    ;

orderedBase64RLEMinusName
    : ORDEREDNAME UNDERSCORE BASE64RLEMINUSNAME
    | BASE64RLEMINUSNAME UNDERSCORE ORDEREDNAME
    ;
      

MULTINAME : 'MULTI' ;
IDNAME : 'IDS' ;
BASE64RLEMINUSNAME : 'BASE64RLEMINUS' ;
MISSIONIDNAME : 'MISSIONID' ;
RAIDIDNAME : 'RAIDID' ;
QUESTIDNAME : 'QUESTID' ;
ORDEREDNAME : 'ORDERED' ;
COLON : ':' ;
COMMA : ',' ;
SEMICOLON : ';' ;
NUMBER : [1-9][0-9]* ;
LBRACE : '{' ;
RBRACE : '}' ;
UNDERSCORE : '_' ;
ASSIGNCARDINALITY : '=' ;
BASE64RLEMINUSDATA : [A-Za-z0-9+/-] ;