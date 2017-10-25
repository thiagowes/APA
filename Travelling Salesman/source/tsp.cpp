#include "tsp.hpp"
#include <iostream>

TSP :: TSP(){}

void TSP:: BuildAdjMatrix(const char *fileName){
	int cost;
	ifstream file(fileName);
	file >> size_;
	AdjMatrix_.resize(size_);

	for(int i = 0; i < size_; i++){
		AdjMatrix_[i].resize(size_);
		for(int j = 0; j < size_; j++){
			file >> cost;
			AdjMatrix_[i][j] = cost;
		}
	}

	file.close();

	cout << "Instância: " << fileName << endl;
}

/*fonte do código para gerar as combinações: 
  http://www.geeksforgeeks.org/find-combinations-k-bit-numbers-n-bits-set-1-n-k-sorted-order/*/
void TSP :: GenerateCombinations(int nBits){
	vector<string> bits[nBits+1][nBits+1];
	string combinationStr;
    
	//armazena todos os nBits. Nesse momento todos são zero
	for(int i = 0; i < nBits; i++){
		combinationStr += "0";
		bits[i][0].push_back(combinationStr);
	}

	//insere a combinção referente ao conjunto nulo
	Combination_.push_back(combinationStr);
	
	//realiza a formação dos demais conjuntos
	for(int i = 1; i <= nBits; i++){
		for(int j = 1; j <= i; j++){
			//insere os bits 0
			for(string combinationStr : bits[i - 1][j])
				bits[i][j].push_back("0" + combinationStr);

	 		//insere os bits 1
			for(string combinationStr : bits[i - 1][j - 1])
				bits[i][j].push_back("1" + combinationStr);
        }
	
    }

	//insere todos os conjuntos formados
	for(int i = 1; i <= nBits; i++){
		for(string combinationStr : bits[nBits][i]){
			Combination_.push_back(combinationStr);
		}
	}
	
}

void TSP :: BuildMatrixTSP(string combination){
	vector<int> combinationInt, auxCombinationInt;
	int number = size_;
	int minCost = 0, auxCost;
	SelectedPath auxPath;
	string index;
	bool match = false;
	
	/*converte o conjunto do tipo string para inteiro, passando também 
	 de binário para decimal. Ex: 111 -> {4, 3, 2}*/
	for(int i = 0; i < combination.size(); i++){
		if(combination[i] == '1')
			combinationInt.push_back(number);
		number--;
	}
	
	//calcula as linhas da coluna, exceto a primeira que é 0
	for(int line = 1; line < size_; line++){
		//conjunto com apenas um elemento	
		if(combinationInt.size() == 1){
			//verifica se a cidade pertence ao conjunto
			if(combinationInt[0] == line + 1)
				minCost = 0;
			else
				//equação: dij + g(j, {0})
				minCost = AdjMatrix_[line][combinationInt[0] - 1] + MatrixTSP_[combinationInt[0] - 1][Combination_[0]];
		}
		//conjunto com dois ou mais elementos
		else{
			//verifica se a cidade pertence ao conjunto
			for(int i = 0; i < combinationInt.size(); i++){
				if(line + 1 == combinationInt[i])
					match = true;
			}
			if(match)
				minCost = 0;
			else{
				//analisa os casos possíveis do conjunto
				for(int i = 0; i < combinationInt.size(); i++){
					for(int j = 0; j < combination.size(); j++)
						index  += "0";
					for(int j = 0; j < combinationInt.size(); j++)
						auxCombinationInt.push_back(combinationInt[j]);
					
					//remove a cidade que vai ser analisada
					auxCombinationInt.erase(auxCombinationInt.begin() + i);
					
					//obtém o conjunto sem a cidade que vai ser analisada
					for(int j = 0; j < auxCombinationInt.size(); j++)
						index[size_ - auxCombinationInt[j]] = '1';
					
					//equação: dij + g(j, {S} - j)
					auxCost = AdjMatrix_[line][combinationInt[i] - 1] + MatrixTSP_[combinationInt[i] - 1][index];

					if(minCost == 0 || auxCost < minCost){
						//atualiza o custo mínimo e a cidade escolhida
						minCost = auxCost;
						auxPath.path = combinationInt[i];
					}
					
					//reinicia as variáveis para a análise do próximo caso
					index.clear();
					auxCombinationInt.clear();
				}
				
				//insere a cidade escolhida com seu respectivo conjunto
				auxPath.key = combination;
				Path_.push_back(auxPath);				
			}
		}
		
		//insere o custo mínimo na matriz solução		
		MatrixTSP_[line][combination] = minCost;
		//reinica a variável para analisar a próxima linha
		match = false;
	}

}

void TSP :: CalculateLastColumn(string combination){
	vector<int> combinationInt, auxCombinationInt;
	int number = size_;
	int minCost = 0, auxCost;
	SelectedPath auxPath;
	string index;

	/*converte o conjunto do tipo string para inteiro, passando também 
	 de binário para decimal. Ex: 111 -> {4, 3, 2}*/
	for(int i = 0; i < combination.size(); i++){
		if(combination[i] == '1')
			combinationInt.push_back(number);
		number--;
	}

	//analisa os casos possíveis do conjunto
	for(int j = 0; j < combinationInt.size(); j++){

		for(int i = 0; i < combinationInt.size(); i++)
			auxCombinationInt.push_back(combinationInt[i]);

		for(int i = 0; i < combination.size(); i++)
			index  += "0";

		//remove a cidade que vai ser analisada
		auxCombinationInt.erase(auxCombinationInt.begin() + j);

		//obtém o conjunto sem a cidade que vai ser analisada
		for(int i = 0; i < auxCombinationInt.size(); i++)
			index[size_ - auxCombinationInt[i]] = '1';
		
		//equação: dij + g(j, {S} - j)
		auxCost = AdjMatrix_[0][combinationInt[j] - 1] + MatrixTSP_[combinationInt[j] - 1][index];

		if(minCost == 0 || auxCost < minCost){
			//atualiza o custo mínimo e a cidade escolhida
			minCost = auxCost;
			auxPath.path = combinationInt[j];
		}
	
		//reinicia as variáveis para a análise do próximo caso
		index.clear();
		auxCombinationInt.clear();
	}

	//insere a cidade escolhida com seu respectivo conjunto
	auxPath.key = combination;
	Path_.push_back(auxPath);

	//insere o custo mínimo na matriz solução
	MatrixTSP_[0][combination] = minCost;
}

void TSP :: getAllPath(){
	string index;
	vector<int> combinationInt;
	int number = size_;
	int i = Path_.size() - 1;

	//insere a cidade de origem
	showPath_.push_back(1);

	while(1){

		/*converte o conjunto do tipo string para inteiro, passando também 
		  de binário para decimal. Ex: 111 -> {4, 3, 2}*/
		for(int j = 0; j < Path_[0].key.size(); j++){
			if(Path_[i].key[j] == '1')
				combinationInt.push_back(number);
			number--;
		}
		
		/*obtém o próximo conjunto que possuí a próxima cidade selecionada, 
		  retirando do conjunto atual a cidade que acabou de ser selecioanda*/
		for(int j = 0; j < combinationInt.size(); j++){
			if(combinationInt[j] == Path_[i].path){
				combinationInt.erase(combinationInt.begin() + j);
				break;
			}
		}
	
		/*insere a última cidade antes de voltar para o ponto de partida, que é o próprio
		  elemento do conjunto, já que há só um elemento nele*/
		if(showPath_.size() == size_ - 1){
			showPath_.push_back(combinationInt[0]);
			break;
		}
		
		
		for(int j = 0; j < Path_[0].key.size(); j++)
			index  += "0";

		//obtém o próximo conjunto do tipo string representado em binário a ser analisado
		for(int j = 0; j < combinationInt.size(); j++)
			index[size_ - combinationInt[j]] = '1';
		
		//insere a cidade que faz parte do circuito
		showPath_.push_back(Path_[i].path);
	
		//procura o índice onde se encotra o conjunto que será analisado
		for(int j = 0; j < Path_.size(); j++){
			if(index == Path_[j].key){
				//atualiza o índice
				i = j;
				break;
			}
		} 

		//reinicia as variáveis para a próxima análise
		combinationInt.clear();
		index.clear();
		number = size_;
	}

	//Por último insere a cidade de origem, para onde se deve retornar
	showPath_.push_back(1);
}

void TSP :: ShowPath(){
	//busca qual circuito foi realizado
	getAllPath();
	cout << "Circuito: ";
	for(int i = 0; i < showPath_.size(); i++){
		if(i != showPath_.size() - 1)
			cout << showPath_[i] << "-->";
		else
			cout << showPath_[i];
	}
	cout << endl;
}

void TSP :: SolutionTSP(){
	//gera as combinações que dão origem aos conjuntos 
	GenerateCombinations(size_ - 1);
	int column = Combination_.size();
	MatrixTSP_.resize(size_);
	
	//iniciliazando a primeira coluna
	for(int i = 0; i < size_; i++)
		MatrixTSP_[i][Combination_[0]] = AdjMatrix_[i][0];
	
	//calculando a segunda coluna até a penúltima
	for(int i = 1; i < column-1; i++)
		BuildMatrixTSP(Combination_[i]);

	//calculando a última coluna
	CalculateLastColumn(Combination_[column - 1]);

	cout << "Valor: " << MatrixTSP_[0][Combination_[Combination_.size() - 1]] << endl;
	
	//Mostra o circuito
	ShowPath();

}

TSP :: ~TSP(){}
