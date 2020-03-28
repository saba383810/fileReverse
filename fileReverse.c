#include <stdio.h>
#include <stdlib.h>

#define LineMax 100

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("コマンドライン引数エラー\n引数の数は2つです。もう一度実行しなおしてください。\n");
        return -1;
    }
    FILE * fp;
    FILE *outputfile;
    char Lines[LineMax][256];
    int lineCnt=0;

    //ファイル読み込み
    fp = fopen(argv[1], "r");
    if( fp == NULL ){
        printf( "読み込み用ファイルオープンエラー\n" );
        return -1;
    }
    //一つ一つのラインを配列にいれる
    for(unsigned int i = 0; i < LineMax && fgets( Lines[i], sizeof(Lines[i]) , fp ) != NULL; i++) lineCnt++;
    int LinesNum[lineCnt];
    for(int i=0;i<lineCnt;i++) LinesNum[i] = 0;//配列を0で初期化
    //リバース
    for(int row = 0; row < lineCnt; row++){
        //一行の文字数をカウント
        int count = 0;
        while(Lines[row][count] != '\0'&& Lines[row][count] != '\n' && Lines[row][count] != '\r') count++;
        //printf("%d番,%d",row,count);
        LinesNum[row] = count;
        //改行文字を抜いた反転
        for(int i = 0; count - i -1> i; i++){
            char temp = Lines[row][i];
            Lines[row][i] = Lines[row][count - i-1];
            Lines[row][count - i-1] = temp;
        }
    }
    fclose( fp );
    //もともとあるデータを削除する。
    remove(argv[2]);
    for(int i =0; i < lineCnt; i++){
        for(int j = 0; j <= LinesNum[i]; j++){
            outputfile = fopen(argv[2], "a");
            if (outputfile == NULL) {          // オープンに失敗した場合
                printf("書き込み用ファイルオープンエラー\n");         // エラーメッセージを出して終了
                return -1;
            }
            fprintf(outputfile,"%c", Lines[i][j]); // ファイルに書く
            fclose(outputfile);
        }
    }
    printf("ファイルの書き込みが正常に終了しました。");
    return 0;
}