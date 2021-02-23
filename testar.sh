#!/bin/bash
ARQUIVOS=$(ls entradas)
SAIDA="saidas"

if [ ! -d "$SAIDA" ]; 
then
  mkdir $SAIDA
fi

for i in $ARQUIVOS;
do
	echo -e "Rodando programa para $i..."

    NEW_NAME=${i%.txt}.out
	time ./ortografia < entradas/$i > $SAIDA/$NEW_NAME

	RES=$(diff $SAIDA/$NEW_NAME esperadas/${i%.txt}-saida.txt)

	if [ ! -z "$RES" ]
	then
		echo -e "$(tput setaf 1 && tput bold)ERRO! A saída não está correta para $i$(tput sgr 0)\n"
	else
		echo -e "$(tput setaf 2 && tput bold)SUCESSO!$(tput sgr 0)\n"
	fi
done