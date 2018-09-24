#include <stdio.h>
#include <string.h>
// Functions
int match(int diagScore, int mismatchPenalty, char q, char p){
    if (q==p){
        return diagScore+mismatchPenalty; }
    else{
        return diagScore-mismatchPenalty; }}
int gapQ(int leftScore, int gapPenalty){
    return leftScore-gapPenalty; }
int gapP(int topScore, int gapPenalty){
    return topScore-gapPenalty; }
int maxScore(int matchScore, int gapQScore, int gapPScore){
    if (matchScore>=gapQScore && matchScore>=gapPScore){
        return matchScore; }
    else if(gapQScore > gapPScore){
        return gapQScore; }
    else{
        return gapPScore; }}
void printScoreTable(int qlen, int plen, char seqQ[qlen], char seqP[plen], int scoreMatrix[qlen][plen]){
    int seqPIndex = 0;
    // Header
    printf("SeqQ is %s at %i nt long\n", seqQ, qlen);
    printf("SeqP is %s at %i nt long\n", seqP, plen);
    printf("\t-\t-");
    for(int q=0; q<qlen; q++){
        printf("\t%c",seqQ[q]); }
    printf("\n");
    // Scoring Matrix
    for(int p=0; p<plen-1; p++){
        for(int q=0; q<qlen-1; q++){
            if(p==0){
                if(seqPIndex==0){
                    printf("\t-"); }
                else{
                    printf("\t%c", seqP[seqPIndex-1]); }}
            else{
                printf("\t%i", (int)scoreMatrix[seqPIndex][p]); }}
        printf("\n");
        seqPIndex++; }}
int main(){
    int const gapPenalty = 1;
    int const mismatchPenalty = 1;
    // Sequences to align
    char seqQ[] = "GCTGGAAGGCAT";
    char seqP[] = "GCAGAGCACG";
    int scoreMatrix [strlen(seqQ)+1][strlen(seqP)+1];
    // Initialize first row and column of score matrix
    for (int q=0; q<strlen(seqQ)+1; q++){
        scoreMatrix[q][0] = -1*q; }
    for (int p=1; p<strlen(seqP)+1; p++){
        scoreMatrix[0][p] = -1*p; }
    // Calculate scores across alignment
    for(int q=1; q<(strlen(seqQ)+1); q++){
        for(int p=1; p<(strlen(seqP)+1); p++){
            scoreMatrix [q][p] = maxScore(match(scoreMatrix[q-1][p-1], mismatchPenalty, seqQ[q],seqP[p]),gapQ(scoreMatrix[q-1][p], gapPenalty), gapP(scoreMatrix[q][p-1], gapPenalty)); }}
    // Print alignment table
    printScoreTable(strlen(seqQ), strlen(seqP), seqQ, seqP, scoreMatrix);
    return 0; }
