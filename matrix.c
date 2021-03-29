#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

/* Method Declaration */
int** create_matrix(int row, int col);                          //matrix 생성 함수
void print_matrix(int** matrix, int row, int col);              //matrix 출력 함수
int free_matrix(int** matrix, int row, int col);                //동적할당 된 matrix 해제 함수
int fill_data(int** matrix, int row, int col);                  //matrix 에 램덤 값 넣는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);      //행렬 합 계산 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //행렬 뺄셈 계산 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);       //전치행렬 구해주는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);      //전치행렬과의 곱 출력 함수

int main()
{

    char command;   //메뉴 입력 시 받은 char 형 command 변수
    printf("[----- [정종현]  [2018038051] -----]\n");

    int row, col;   //행, 열 변수 선언
    srand(time(NULL));  //난수 생성 함수

    printf("Input row and col : ");       
    scanf("%d %d", &row, &col);             //행과 열 입력
    int** matrix_a = create_matrix(row, col);   //matrix_a 생성
    int** matrix_b = create_matrix(row, col);   //matrix_b 생성
    int** matrix_a_t = create_matrix(col, row); //matrix_a_t 생성 (matrix_a의 전치행렬)
    int result;

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}  //matrix가 생성되지 않으면 프로그램 종료.

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //메뉴를 입력받음.

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n"); //matrix에 값을 입력 받음
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");   //matrix 출력
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");   //두 matrix 를 더한 값 출력
            result=addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n"); //두 matrix 를 뺀 값 출력
            result=subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");    //matrix a와 a의 전치행렬 출력
            printf("matrix_a\n");
            print_matrix(matrix_a,row,col);
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            printf("matrix_a_t\n");
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");    //matrix_a와 a의 전치행렬의 곱 출력
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");    //동적할당 된 matrix 해제
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:    //유효하지 않은 값을 입력했을 때 경고 문 출력. (예외처리)
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}


/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if(row<=0||col<=0){printf("Check the sizes of row and col! \n"); return NULL;} // 행값과 열값이 0보다 작은 값이 들어오면, 경고문을 출력하고 NULL값을 리턴한다.(예외처리)
    
    else{
    int **matrix, i;
    matrix=(int**)malloc(row*sizeof(*matrix)); //포인터변수크기 * 행 size의 배열 동적할당
    for(i=0;i<row;i++){
        matrix[i]=(int*)malloc(col*sizeof(**matrix));//int형 크기* 열 size 배열 동적할당
        }
    
    if(fill_data(matrix,row,col))
        return matrix; //값이 성공적으로 채워지면 matrix를 반환한다.
    else if(matrix==NULL) {printf("fail to fill data\n"); return NULL;}// 값이 성공적으로 채워지지 않으면 경고문을 출력한다.
    
    }
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%4d",matrix[i][j]); //[i][j]번째 값을 2중 for문으로 출력해준다.
        }
        printf("\n");   //행이 바뀌면 줄바꿈을 해준다.
    }
    printf("\n");
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    for(int i=0;i<row;i++) free(matrix[i]); //동적할당된 배열을 for문을 돌면서 하나씩 해제해준다.
    free(matrix);   //배열을 가리키는 동적할당 된 matrix를 해제해준다.
    
    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    for(int i =0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix[i][j]=rand()%20; // 0~19 사이의 값을 갖는 램덤값으로 행렬을 채운다.
        }
    }
    return 1; //값을 채우는 데에 이상이 없을 경우.
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%5d",matrix_a[i][j]+matrix_b[i][j]);//더한값을 출력
        }printf("\n");//행 바뀌면 줄 바꿈
    }printf("\n");
    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%5d",matrix_a[i][j]-matrix_b[i][j]);//뺀 값을 출력
        }printf("\n");//행 바뀌면 줄 바꿈
    }printf("\n");
    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix_t[i][j]=matrix[j][i];    //행과 열 순서가 바뀌므로 전치행렬에 matrix_t[i][j]에 matrix[j][i] 값을 넣어준다.
        }
    }
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int sum=0;
    int colbegin;   //행 X 열 연산 중 행 연산을 먼저 하기 위한 변수 선언
    for(int i=0;i<row;i++){         //행렬 곱의 다음 행으로 이동
        
        for(int colbegin=0;colbegin<row;colbegin++){    //matrix_a의 다음 행 이동
        

            for(int j=0;j<col;j++){                     //고정된 matrix_a의 행에 
                                                        //matrix_a_t의 열 값들을 각각 곱해 더해준다.
                sum+=matrix_a[i][j]*matrix_t[j][colbegin];
            
            }printf("%5d",sum); sum=0; //더해준 값들을 출력.

        }printf("\n");  //행렬 곱 행 바뀜 시 줄바꿈

    }printf("\n");

    return 1;
}

