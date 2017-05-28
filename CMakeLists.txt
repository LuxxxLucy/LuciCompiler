cmake_minimum_required(VERSION 3.0)
project(lucc-c)

include(FindFLEX)
include(FindBISON)

flex_target(LEXER syntax.lex ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
bison_target(PARSER parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
add_flex_bison_dependency(LEXER PARSER)

set_source_files_properties(lexer.l parser.y PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable(lucc
    abstract_syntax.c
    abstract_syntax.h
    env.c
    env.h
    error_message.c
    error_message.h
    escape.c
    escape.h
    frame.h
    frame-mips.c
    tree.c
    tree.h
    lexer.l
    main.c
    parser-wrap.h
    parser.y
    ppAST.c
    ppAST.h
    pptree.c
    pptree.h
    semantic.c
    semantic.h
    symbol.c
    symbol.h
    table.c
    table.h
    temp.c
    temp.h
    translate.c
    translate.h
    types.c
    types.h
    utils.c
    utils.h
    ${FLEX_LEXER_OUTPUTS}
    ${BISON_PARSER_OUTPUTS}
)
