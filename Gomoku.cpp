wu#include <algorithm>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <string>

#define illegal ( ! inboard(x + dx[u] * i, y + dy[u] * i) || p[x + dx[u] * i][y + dy[u] * i] != 0)//不合法 

#define the_same_color issame(x + dx[u] * i, y + dy[u] * i, p[x][y])//是否同色 

const int N = 16;
const int mod = 998244353;
 
int p[20][20], dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 }, dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int s = 0, s0, AI_start = 1, action[2][300], cnt = 0;
bool is_end = false;

//===========================================================================================================================

bool inboard( int x, int y ){ return ( y >= 1 && y <= N && x >= 1 && x <= N); }
bool is_ok( int x, int y ){ return p[x][y] == 0 && inboard(x, y); }
int issame( int x, int y, int key ){ if( !inboard( x, y ) ) return false; return( p[x][y] == key || p[x][y] + key == 0 ); }

//===========================================================================================================================

int Print_chessboard( int i, int j ){//打印棋盘 
	if( p[i][j] ==  1 ) return printf("●"); if( p[i][j] == -1 ) return printf("▲");
	if( p[i][j] ==  2 ) return printf("○"); if( p[i][j] == -2 ) return printf("△");
    if( i == 1 ){ if( j == 1 ) return printf("┗-"); if( j == N ) return printf("┛ "); return printf("┷-"); }
	if( i == N ){ if( j == 1 ) return printf("┏-"); if( j == N ) return printf("┓ "); return printf("┯-"); }
	if( j == 1 ) return printf("┠-"); if( j == N ) return printf("┨ ");
	return printf("┼-");
}
void Print_interface(){
    system("cls");
    int x = 0, y = 0, keyr = 0, keyc = 0; char ch = 'A';
	printf("      ");
	for( int i = 1; i <= N; i ++ ) printf( "%c ", ch++ );
	for( int i = N; i >= 1; i -- ){
		printf( "\n   %2d", i );
		for( int j = 1; j <= N; j++){
			Print_chessboard( i, j );
			if( p[i][j] < 0 ) keyr = i, keyc = j;
		}
		printf( "%d", i );
    }
	printf("\n      "); ch = 'A';
	for( int i = 1; i <= N; i ++ ) printf( "%c ", ch++ ); puts("\n");
	if( s0 == AI_start ) puts("  AI holds black, players hold white, press q + any number to query the manual"); else puts("  AI holds white, players hold black, press q + any number to query the manual");
	ch = 'A'; if( keyr ) printf( "  Last position：%c%d\n", ch + keyc - 1, keyr );
}
void init(){
    system("color f0");
	puts("Press 1 or 2 and Enter to continue:\n    Press 1: AI takes the lead in black\n    Press 2: Player takes the lead in black");
	scanf( "%d", &s ); if( s != 1 && s != 2 ) return init();
    s0 = s;
    for( int i = 0; i <= N + 1; i ++ ) for( int j = 0; j <= N + 1; j ++ ) p[i][j] = 0;
	Print_interface();
	for( int j = 0; j < 300; j ++ ) action[0][j] = action[1][j] = 0;
}

//===========================================================================================================================

int num_same_color( int x, int y, int u ){
	int i = x + dx[u], j = y + dy[u], res = 0, now = p[x][y];
    if( ! now ) return 0;
    while( issame( i, j, now ) ) res ++, i += dx[u], j += dy[u];
    return res;
}
int Live_three( int x, int y ){
	int key = p[x][y], res = 0, flag = 2;
	for( int u = 0, i; u < 4; u ++ ){
		int tot = 1;
		for( i =  1; the_same_color; i ++ ) tot ++; if( illegal ) continue ; i ++; if( illegal ) flag --;
		for( i = -1; the_same_color; i -- ) tot ++; if( illegal ) continue ; i --; if( illegal ) flag --;
		if ( tot == 3 && flag ) res ++;
    }
	for( int u = 0, i; u < 8; u ++ ){
		int  tot = 0; bool flag = true;
		for( i = 1; the_same_color || flag; i ++ ){
			if( !the_same_color ){ if( flag && p[x + dx[u] * i][y + dy[u] * i] ) tot -= 10; flag = false; }
			tot++;
		}
		if( illegal ) continue ; if( p[x + dx[u] * --i][y + dy[u] * i] == 0 ) continue ; for( i = 1; the_same_color; i ++ ) tot ++;
        if( illegal ) continue ; if( tot == 3 ) res ++;
	}
	return res;
}
int live_four( int x, int y ){
    int res = 0;
    for( int u = 0, i; u < 4; u++){
		int tot = 1;
		for( i =  1; the_same_color; i ++ ) tot ++; if( illegal ) continue ;
		for( i = -1; the_same_color; i -- ) tot ++; if( illegal ) continue ;
		if( tot == 4 ) res ++;
    }
	return res;
}
int Into_five( int x, int y ){
	int res = 0;
	for( int u = 0, i; u < 8; u ++ ){
		int  tot = 0; bool flag = true;
		for( i = 1; the_same_color || flag; i ++ ){
			if( !the_same_color ){
				if( p[x + dx[u] * i][y + dy[u] * i] ) tot -= 10;
				flag = false;
			}
			tot++;
		}
		if( !inboard( x + dx[u] * --i, y + dy[u] * i ) ) continue ;
		for( i = -1; the_same_color; i -- ) tot ++;
		if( tot == 4 ) res ++;
	}
	return res;
}
int Rush_four( int x, int y ){ return Into_five(x, y) - live_four(x, y) * 2; }
bool overline( int x, int y ){ for( int u = 0; u < 4; u ++ )if( num_same_color(x, y, u) + num_same_color(x, y, u + 4) > 4 ) return true; return false; }//长连禁手
bool Forbidden( int x, int y ){
	if( issame( x, y, 2 ) ) return false;
	return overline(x, y) || Live_three(x, y) > 1 || live_four(x, y) + Rush_four(x, y) > 1;
}
bool is_the_end( int x, int y ){
	for( int u = 0; u < 4; u ++ ) if( num_same_color( x, y, u ) + num_same_color( x, y, u + 4 ) >= 4 ) is_end = true;
    if( is_end ) return true; is_end = Forbidden( x, y ); return is_end;
}
void Luo_Zi(int x, int y){
    p[x][y] = s == s0 ? -1 : -2;
	for( int i = 0; i <= N; i ++ )
		for( int j = 0; j <= N; j ++ ){
			if( i == x && j == y ) continue ;
			if( p[i][j] < 0 ) p[i][j] *= -1;
	}
	Print_interface();
	if( Forbidden( x, y ) ){ puts("Forbidden!"); if( s0 == 1 ) puts("Perfect synchronization"); else puts("Lost synchronization"); Sleep(2077); }
	if( is_the_end( x, y ) ){ if( s ^  AI_start ) puts("Perfect synchronization"); else puts("Lost synchronization"); Sleep(2077); }
	action[0][cnt] = x, action[1][cnt++] = y;
}

//===========================================================================================================================

int point( int x, int y ){
	if( Forbidden( x, y ) ) return 0;
	if( is_the_end( x, y ) ){ is_end = false; return 10000; }
	int res = live_four( x, y ) * 2000 + Live_three(x, y) * 100 + Rush_four(x, y) * 120;
	for( int u = 0; u < 8; u ++ ) if( p[x + dx[u]][y + dy[u]] ) res += 1;
	return res;
}
int AI_max( int x ){
	int maxn = -100000, cur;
	for( int i = 1; i <= N; i ++ ) 
		for( int j = 1; j <= N; j ++ ){
			if( !is_ok( i, j ) ) continue;
			p[i][j] = s0; cur = point( i, j );
			if( cur == 0 ){ p[i][j] = 0; continue ; }
			if( cur == 10000 ){ p[i][j] = 0; return 10000; }
			p[i][j] = 0;
			if( cur - x * 2 > maxn ) maxn = cur - x * 2;
	}
	return maxn;
}
int AI_min( ){
	int maxn = 100000, cur;
	for( int i = 1; i <= N; i ++ )
		for( int j = 1; j <= N; j ++ ){
			if( !is_ok( i, j ) ) continue;
			p[i][j] = 3 - s0;
			cur = point(i, j);
			if( cur == 0 ) { p[i][j] = 0; continue ; }
			if (cur == 10000) { p[i][j] = 0; return -10000; }
			cur = AI_max(cur); p[i][j] = 0;
		if( cur < maxn ) maxn = cur;
	}
	return maxn;
}
void AI( ){
	Print_interface(); printf("   loading......    ");
	if( p[8][8] == 0 ) return Luo_Zi( 8, 8 );
	int maxn = -114514, mxx, mxy, cur;
	for( int i = 1; i <= N; i ++ ){
		for( int j = 1; j <= N; j ++ ){
			if( ! is_ok( i, j ) ) continue; p[i][j] = s0; cur = point( i, j );
			if( cur <= 0 ){ p[i][j] = 0; continue; }
			if( cur >= 10000 ) return Luo_Zi( i, j );
			cur = AI_min( ); p[i][j] = 0;
			if( cur > maxn ) maxn = cur, mxx = i, mxy = j;
		}
	}
	return Luo_Zi( mxx, mxy );
}

//===========================================================================================================================

void print_manual(){
	char ch = 'A';
	printf("\n  Black's position: "); for( int i = 0; i < cnt; i += 2) printf("  %c%d", ch + action[1][i] - 1, action[0][i] );
	printf("\n  White's position: "); for( int i = 1; i < cnt; i += 2) printf("  %c%d", ch + action[1][i] - 1, action[0][i] );
	Sleep(5000);
}
void player(){
	Print_interface();
	printf("  Your round： ");
	char c = '\n'; int x = 0, y = 0;
	while( c < '0' ) scanf( "%c%d", &c, &x );
    if( c == 'q' ){ print_manual(); return player(); }
    if( c < 'a' ) y = c - 'A' + 1; else y = c - 'a' + 1;
	if (!is_ok(x, y)){ printf("Warning : You can't put chess here, or you will lost synchronization"); Sleep(2077); return player(); }
	Luo_Zi(x, y);
}

//===========================================================================================================================

int main(){
	init();
	while( !is_end ){ if( s == AI_start ) AI(); else player(); s = 3 - s; }
	system("cls");
	puts("\n\n\n\n\n\n\n                         Gameover  \n\n\n\n\n\n");
	return 0;
}
