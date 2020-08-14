#!/bin/bash
ARQUIVOS=$(ls arq/)
for i in $ARQUIVOS;
do
	echo -e "Rodando programa para $i..."
	time ./ortografia < arq/$i > saida.txt
	RES=$(diff saida.txt saidas-corretas/${i%.txt}-saida.txt)
	if [ ! -z "$RES" ]
	then
		echo -e "$(tput setaf 1 && tput bold)ERRO! A saída não está correta para $i$(tput sgr 0)\n"
	else
		echo -e "SUCESSO!\n"
	fi
done