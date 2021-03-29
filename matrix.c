#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

/* Method Declaration */
int** create_matrix(int row, int col);                          //matrix ���� �Լ�
void print_matrix(int** matrix, int row, int col);              //matrix ��� �Լ�
int free_matrix(int** matrix, int row, int col);                //�����Ҵ� �� matrix ���� �Լ�
int fill_data(int** matrix, int row, int col);                  //matrix �� ���� �� �ִ� �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);      //��� �� ��� �Լ�
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //��� ���� ��� �Լ�
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);       //��ġ��� �����ִ� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);      //��ġ��İ��� �� ��� �Լ�

int main()
{

    char command;   //�޴� �Է� �� ���� char �� command ����
    printf("[----- [������]  [2018038051] -----]\n");

    int row, col;   //��, �� ���� ����
    srand(time(NULL));  //���� ���� �Լ�

    printf("Input row and col : ");       
    scanf("%d %d", &row, &col);             //��� �� �Է�
    int** matrix_a = create_matrix(row, col);   //matrix_a ����
    int** matrix_b = create_matrix(row, col);   //matrix_b ����
    int** matrix_a_t = create_matrix(col, row); //matrix_a_t ���� (matrix_a�� ��ġ���)
    int result;

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}  //matrix�� �������� ������ ���α׷� ����.

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
        scanf(" %c", &command); //�޴��� �Է¹���.

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n"); //matrix�� ���� �Է� ����
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");   //matrix ���
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");   //�� matrix �� ���� �� ���
            result=addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n"); //�� matrix �� �� �� ���
            result=subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");    //matrix a�� a�� ��ġ��� ���
            printf("matrix_a\n");
            print_matrix(matrix_a,row,col);
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            printf("matrix_a_t\n");
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");    //matrix_a�� a�� ��ġ����� �� ���
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");    //�����Ҵ� �� matrix ����
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:    //��ȿ���� ���� ���� �Է����� �� ��� �� ���. (����ó��)
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}


/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if(row<=0||col<=0){printf("Check the sizes of row and col! \n"); return NULL;} // �ప�� ������ 0���� ���� ���� ������, ����� ����ϰ� NULL���� �����Ѵ�.(����ó��)
    
    else{
    int **matrix, i;
    matrix=(int**)malloc(row*sizeof(*matrix)); //�����ͺ���ũ�� * �� size�� �迭 �����Ҵ�
    for(i=0;i<row;i++){
        matrix[i]=(int*)malloc(col*sizeof(**matrix));//int�� ũ��* �� size �迭 �����Ҵ�
        }
    
    if(fill_data(matrix,row,col))
        return matrix; //���� ���������� ä������ matrix�� ��ȯ�Ѵ�.
    else if(matrix==NULL) {printf("fail to fill data\n"); return NULL;}// ���� ���������� ä������ ������ ����� ����Ѵ�.
    
    }
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%4d",matrix[i][j]); //[i][j]��° ���� 2�� for������ ������ش�.
        }
        printf("\n");   //���� �ٲ�� �ٹٲ��� ���ش�.
    }
    printf("\n");
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    for(int i=0;i<row;i++) free(matrix[i]); //�����Ҵ�� �迭�� for���� ���鼭 �ϳ��� �������ش�.
    free(matrix);   //�迭�� ����Ű�� �����Ҵ� �� matrix�� �������ش�.
    
    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    for(int i =0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix[i][j]=rand()%20; // 0~19 ������ ���� ���� ���������� ����� ä���.
        }
    }
    return 1; //���� ä��� ���� �̻��� ���� ���.
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%5d",matrix_a[i][j]+matrix_b[i][j]);//���Ѱ��� ���
        }printf("\n");//�� �ٲ�� �� �ٲ�
    }printf("\n");
    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%5d",matrix_a[i][j]-matrix_b[i][j]);//�� ���� ���
        }printf("\n");//�� �ٲ�� �� �ٲ�
    }printf("\n");
    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix_t[i][j]=matrix[j][i];    //��� �� ������ �ٲ�Ƿ� ��ġ��Ŀ� matrix_t[i][j]�� matrix[j][i] ���� �־��ش�.
        }
    }
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int sum=0;
    int colbegin;   //�� X �� ���� �� �� ������ ���� �ϱ� ���� ���� ����
    for(int i=0;i<row;i++){         //��� ���� ���� ������ �̵�
        
        for(int colbegin=0;colbegin<row;colbegin++){    //matrix_a�� ���� �� �̵�
        

            for(int j=0;j<col;j++){                     //������ matrix_a�� �࿡ 
                                                        //matrix_a_t�� �� ������ ���� ���� �����ش�.
                sum+=matrix_a[i][j]*matrix_t[j][colbegin];
            
            }printf("%5d",sum); sum=0; //������ ������ ���.

        }printf("\n");  //��� �� �� �ٲ� �� �ٹٲ�

    }printf("\n");

    return 1;
}

