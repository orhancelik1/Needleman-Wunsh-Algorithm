#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int match= 5, gap=-5, missmatch=-3; //scoring line

int Max(int num1,int num2,int num3){
	int max;
	if(num1 > num2)
    {
        if(num1 > num3)
        {
            max = num1;
        }
        else
        {
            max = num3;
        }
    }
    else
    {
        if(num2 > num3)
        {
            max = num2;
        }
        else
        {
            max = num3;
        }
    }
	return max;
}


int main(){
	int i,j,num1,num2,num3,c1=0,c2=0;
	char seq1[30]="$CTCGCAGC";  
	char seq2[30]="$CATTCAC";    
	char Tbseq1[30];  //traceback array for seq1 
	char Tbseq2[30];  //traceback array for seq2
	int lenseq1 = strlen(seq1);
	int lenseq2 = strlen(seq2);
	int scoreMatrix[lenseq1][lenseq2];

//building matrix and putting 'alpha' values
    printf("\t");
	for(j=0;j<lenseq2;j++){
    	printf("%c \t",seq2[j]);	
	}
	printf("\n");
	
	for(i=0; i<lenseq1; i++){
		printf("%c \t",seq1[i]);
		
		for(j=0; j<lenseq2; j++){
			if(i==0 || j==0){ //gap penalty values
				if(i==0){
					scoreMatrix[0][j]=j*gap;
					printf("%d\t",scoreMatrix[0][j]);
				}
				else{//j==0
					scoreMatrix[i][0]=i*gap;
					printf("%d\t",scoreMatrix[i][0]);
				}
			}
			else{
				if(seq1[i]==seq2[j]){
					num1=scoreMatrix[i-1][j-1]+match;
					num2=scoreMatrix[i-1][j]+gap;
					num3=scoreMatrix[i][j-1]+gap;
					printf("%d\t",scoreMatrix[i][j]=Max(num1,num2,num3));
				}
				else{
					num1=scoreMatrix[i-1][j-1]+missmatch;
					num2=scoreMatrix[i-1][j]+gap;
					num3=scoreMatrix[i][j-1]+gap;
					printf("%d\t",scoreMatrix[i][j]=Max(num1,num2,num3));
				}
			}
		}
		
		printf("\n\n");
	}
// traceback part
  
    j=lenseq2-1, i=lenseq1-1;
    while(i>0){
        
    
		if(seq1[i]==seq2[j]){  //match condition
	
	
		Tbseq1[c1]=seq1[i];     //Tbseq traceback sequence
		Tbseq2[c2]=seq2[j];
	    c1++ , c2++;           //Tbseq indises
		i--, j--;		       //diagonal move for match 
		}
		else{
			if(scoreMatrix[i-1][j-1]+missmatch == scoreMatrix[i][j]){   //missmatch condition
		
				
				Tbseq1[c1]=seq1[i];
				Tbseq2[c2]=seq2[j];
				c1++ , c2++;
				i--, j--;    //diagonal move for missmatch
			}
			
			else if(scoreMatrix[i][j-1]+gap == scoreMatrix[i][j] ){  //gap condition
		
				
				Tbseq1[c1]='-';
				Tbseq2[c2]=seq2[j];
			    c1++ , c2++;
				j--;           //move left
			}
			
			else if(scoreMatrix[i-1][j]+gap == scoreMatrix[i][j]){   //gap condition
	
			
				Tbseq1[c1]=seq1[i];
				Tbseq2[c2]='-';
				c1++ , c2++;
				i--;          //move top
			}
		
		    
			
		}	
	}		

printf("Optimal Global Alignments:\n");
printf("sequence 1:");
for(i=lenseq1-1;i>=0;i--){
	printf("%c",Tbseq1[i]);
}
printf("\n");
printf("sequence 2:");
for(i=lenseq1-1;i>=0;i--){
	printf("%c",Tbseq2[i]);
}
return 0;	
}




