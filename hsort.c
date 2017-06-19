// Linux gcc
// gcc -O this.file.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#define DC 200000                                   //データの件数

double gettime(void);

double gettime(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec+(double)tv.tv_usec*1e-6;
}

int main(){
    int     i;                                      //制御変数
    int     oya;                                    //親の添え字
    int     osh;                                    //親の添え字保存
    int     oah;                                    //親の値保存
    int     ko;                                     //子の添え字
    int     dc;                                     //データ数
    int     dat[DC+1];                              //データ格納用配列
    double  st;                                     //開始時刻（Start Timeの略）
    double  pt;                                     //処理時間（Processing Timeの略）
    
    srand((unsigned)time(NULL));                    //乱数ジェネレータの初期化
    for(i=0;i<DC;i++)dat[i]=rand()%32768;           //0〜32,767の乱数を生成し配列に格納
    
    st=gettime();                                   //開始時刻の取得
    
    dc=DC;
    //ヒープの構成
    for(oya=(int)((dc-2)/2);oya>=0;oya--){          //最後の親から最初の親まで繰り返し
        osh=oya;                                    //親の添え字を保存
        oah=dat[osh];                               //親の値を保存
        ko=osh+osh+1;                               //左の子の添え字を計算
        while(ko<dc){                               //子の添え字がデータ数以下の場合繰り返し
            if(ko<dc-1 && dat[ko]<dat[ko+1])ko++;   //入れ替え対象の添え字を右の子の添え字に変更
            if(oah>=dat[ko])break;                  //親の保存値の方が子の値より大きい場合はループから抜ける
            dat[osh]=dat[ko];                       //子の値を親の添え字の位置へ代入
            osh=ko;                                 //その時の子の添え字を親の添え字とする
            ko=osh+osh+1;                           //この時の子の添え字を計算
        }
        dat[osh]=oah;                               //保存しておいた親の値を代入
    }
    //ヒープの再構成
    while(dc>0){                                    //添え字の最後から最初まで繰り返し
        dc--;                                       //添え字のデクリメント（これを最初に実行することで上記を成立）
        osh=0;                                      //親の添え字として0を代入
        oah=dat[dc];                                //最後の添え字の値を親の値として保存
        dat[dc]=dat[0];                             //最大値を最後の添え字のエリアへ代入
        ko=osh+osh+1;                               //左の子の添え字を計算
        while(ko<dc){                               //子の添え字がデータ数以下の場合繰り返し
            if(ko<dc-1 && dat[ko]<dat[ko+1])ko++;   //入れ替え対象の添え字を右の子の添え字に変更
            if(oah>=dat[ko])break;                  //親の保存値の方が子の値より大きい場合はループから抜ける
            dat[osh]=dat[ko];                       //子の値を親の添え字の位置へ代入
            osh=ko;                                 //その時の子の添え字を親の添え字とする
            ko=osh+osh+1;                           //この時の子の添え字を計算
        }
        dat[osh]=oah;                               //保存しておいた親の値を代入
    }

    pt=(gettime()-st)*1000;                         //処理時間の計算
    
//  for(i=0;i<DC;i++)printf("%d¥n",dat[i]);         //処理結果の表示
    printf("処理時間： %10.4f ミリ秒¥n",pt);        //処理時間の表示
    return 0;
}