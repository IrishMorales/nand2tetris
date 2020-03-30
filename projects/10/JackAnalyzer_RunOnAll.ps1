#Runs JackAnalyzer on all files in Project 10

#go to project 10 dir of NAND2TETRIS
if ("$PWD>" -ne "C:\Users\Irish\Documents\CS\nand2tetris\projects\10>") {cd C:\Users\Irish\Documents\CS\nand2tetris\projects\10}

$jackfiles = Get-ChildItem -Path "C:\Users\Irish\Documents\CS\nand2tetris\projects\10\" -Recurse -Include *.jack

#run JackAnalyzer on each file
foreach($file in $jackfiles) {
    if ("$PWD>" -ne "C:\Users\Irish\Documents\CS\nand2tetris\projects\10>") {cd ..\projects\10}

    $dir = Split-Path -Path $file -Parent -Resolve | Split-Path -Leaf
    $basefilename = [io.path]::GetFileNameWithoutExtension($file)

    "$dir\$basefilename" | .\JackAnalyzer
    echo ""
}

#check tokenizer output
echo "Beginning token comparison"

cd ../../tools
.\TextComparer ../projects/10/ArrayTest/MainT.xml ../projects/10/ArrayTest/MainTokens.xml
.\TextComparer ../projects/10/ExpressionlessSquare/MainT.xml ../projects/10/ExpressionlessSquare/MainTokens.xml
.\TextComparer ../projects/10/ExpressionlessSquare/SquareT.xml ../projects/10/ExpressionlessSquare/SquareTokens.xml
.\TextComparer ../projects/10/ExpressionlessSquare/SquareGameT.xml ../projects/10/ExpressionlessSquare/SquareGameTokens.xml
.\TextComparer ../projects/10/Square/MainT.xml ../projects/10/Square/MainTokens.xml
.\TextComparer ../projects/10/Square/SquareT.xml ../projects/10/Square/SquareTokens.xml
.\TextComparer ../projects/10/Square/SquareGameT.xml ../projects/10/Square/SquareGameTokens.xml

#check compilationEngine output
echo ""
echo "Beginning compiler comparison"

.\TextComparer ../projects/10/ArrayTest/Main.xml ../projects/10/ArrayTest/MainCompiled.xml
.\TextComparer ../projects/10/ExpressionlessSquare/Main.xml ../projects/10/ExpressionlessSquare/MainCompiled.xml
.\TextComparer ../projects/10/ExpressionlessSquare/Square.xml ../projects/10/ExpressionlessSquare/SquareCompiled.xml
.\TextComparer ../projects/10/ExpressionlessSquare/SquareGame.xml ../projects/10/ExpressionlessSquare/SquareGameCompiled.xml
.\TextComparer ../projects/10/Square/Main.xml ../projects/10/Square/MainCompiled.xml
.\TextComparer ../projects/10/Square/Square.xml ../projects/10/Square/SquareCompiled.xml
.\TextComparer ../projects/10/Square/SquareGame.xml ../projects/10/Square/SquareGameCompiled.xml