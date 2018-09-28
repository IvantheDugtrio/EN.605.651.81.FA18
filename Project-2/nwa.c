#include <stdio.h>
#include <string.h>
// P sequences align to rois
// Q sequences align to columns
//
// Functions
int match(int upperLeftScore,int matchPenalty,int mismatchPenalty,char q,char p){
    if (q==p){
        return upperLeftScore+matchPenalty;}
    else{
        return upperLeftScore+mismatchPenalty;}}
int gapQ(int leftScore,int gapPenalty){
    return leftScore+gapPenalty;}
int gapP(int topScore,int gapPenalty){
    return topScore+gapPenalty;}
int maxScore(int matchScore,int gapQScore,int gapPScore){
    if (matchScore>=gapQScore && matchScore>=gapPScore){
        return matchScore;}
    else if(gapQScore > gapPScore){
        return gapQScore;}
    else{
        return gapPScore;}}
int main(){
    int const gapPenalty=-1;
    int const matchPenalty=1;
    int const mismatchPenalty=-1;
    // Sequences to align
    char const seqQ[]="GCTGGAAGGCAT";
    char const seqP[]="GCAGAGCACG";
    int scoreMatrix[strlen(seqQ)+1][strlen(seqP)+1];
    // Print header
    printf("SeqQ is %s at %i nt long\n",seqQ,(int)strlen(seqQ));
    printf("SeqP is %s at %i nt long\n",seqP,(int)strlen(seqP));
    // Initialize first roi and column of score matrix
    for (int q=0; q<strlen(seqQ)+1; q++){
        scoreMatrix[q][0]=-1*q;}
    for (int p=1; p<strlen(seqP)+1; p++){
        scoreMatrix[0][p]=-1*p;}
    // Calculate and print scores across alignment
    for(int p=0; p<(strlen(seqP)+2); p++){
        for(int q=0; q<(strlen(seqQ)+2); q++){
            // Calculate score of each combination
            if(p>0 && q>0){
                scoreMatrix[q][p]=maxScore(match(scoreMatrix[q-1][p-1],matchPenalty,mismatchPenalty,seqQ[q-1],seqP[p-1]),gapQ(scoreMatrix[q-1][p], gapPenalty),gapP(scoreMatrix[q][p-1],gapPenalty));}
            // Print initialized rois and columns first
            if(p==0 && q==0){
                printf("\t-");}
            else if(p==0){
                if(q==1){
                    printf("\t-");}
                else{
                    printf("\t%c", seqQ[q-2]);}}
            else if(q==0){
                if(p==1){
                    printf("\t-");}
                else{
                    printf("\t%c", seqP[p-2]);}}
            else{
                printf("\t%i", scoreMatrix[q-1][p-1]);}}
        printf("\n");}
    printf("\n");
    // Traceback and find the best alignment
    int q=strlen(seqQ)-1;
    int p=strlen(seqP)-1;
    int gapScore=0;
    int matchScore=0;
    int mismatchScore=0;
    char subSeqQ[50]="";
    char subSeqP[50]="";
    printf("Traceback log\n-------------------------------------------------------------\n");
    for(int i=0; q>-1 && p>-1; i++){
        if(scoreMatrix[q-1][p-1]>=scoreMatrix[q-1][p] && scoreMatrix[q-1][p-1]>=scoreMatrix[q][p-1]){
            subSeqQ[i]=seqQ[q];
            subSeqP[i]=seqP[p];
            if(seqQ[q]==seqP[p]){
                matchScore+=matchPenalty;
                printf("Match\t\tMS: %i\tMMS: %i\tGS: %i\tq: %c%i\tp: %c%i\ti: %i\n",matchScore,mismatchScore,gapScore,seqQ[q],q,seqP[p],p,i);}
            else{
                matchScore+=matchPenalty;
                mismatchScore+=mismatchPenalty;
                printf("Mismatch\tMS: %i\tMMS: %i\tGS: %i\tq: %c%i\tp: %c%i\ti: %i\n",matchScore,mismatchScore,gapScore,seqQ[q],q,seqP[p],p,i);}
        q--;
        p--;}
        else if(scoreMatrix[q-1][p]>=scoreMatrix[q][p-1]){
            subSeqQ[i]=seqQ[q];
            subSeqP[i]='-';
            gapScore+=gapPenalty;
            printf("Gap Up\t\tMS: %i\tMMS: %i\tGS: %i\tq: %c%i\tp: %c%i\ti: %i\n",matchScore,mismatchScore,gapScore,seqQ[q],q,seqP[p],p,i);
            p--;}
        else if(scoreMatrix[q-1][p]<scoreMatrix[q][p-1]){
            subSeqQ[i]='-';
            subSeqP[i]=seqP[p];
            gapScore+=gapPenalty;
            printf("Gap Left\tMS: %i\tMMS: %i\tGS: %i\tq: %c%i\tp: %c%i\ti: %i\n",matchScore,mismatchScore,gapScore,seqQ[q],q,seqP[p],p,i);
            q--;}
        else{
            printf("Error in calculation\n");}}
    // Print alignment metrics
    printf("-------------------------------------------------------------\n");
    printf("Gap score: %i\n", gapScore);
    printf("Match score: %i\n", matchScore);
    printf("Mismatch score: %i\n", mismatchScore);
    printf("Aligned Sequences:\n%s\n%s\n", subSeqQ, subSeqP);
    return 0;}
