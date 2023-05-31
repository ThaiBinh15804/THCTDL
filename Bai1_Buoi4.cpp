#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define item_type int

struct TNode
{
    item_type data;
    TNode *left;
    TNode *right;
};

struct Tree
{
    TNode * root;
};

void Init_TList(Tree &t)
{
    t.root = NULL;
}

TNode *Create_TNode(item_type x)
{
    TNode *p =  new TNode;
    if (p == NULL)
        return NULL;
    
    p->data = x;
    p->left = NULL;
    p->right = NULL;

    return p;
}

int isEmpty(Tree t)
{
    if (t.root == NULL)
        return 1;
    
    return 0;
}

int Insert_TNode(TNode *&root, TNode *p)
{
    if (p == NULL)
        return 0;

    if (root == NULL)
    {
        root = p;
        return 1;
    }
    else
    {
        if (p->data == root->data)
            return 0;

        if (p->data < root->data)
            Insert_TNode(root->left, p);
        else if (p->data > root->data)
            Insert_TNode(root->right, p);
    }   
}


void Create_Tree_From_KeyBoard(TNode *&root, int n)
{
    for (int i = 0; i < n; i++)
    {
        item_type x;
        printf("\nNhap phan tu thu %d: ", i + 1);
        scanf("%d", &x);

        TNode *p = Create_TNode(x);
        Insert_TNode(root, p);
    }
}

void Create_Tree_From_Array(TNode *&root, item_type a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        TNode *p = Create_TNode(a[i]);
        Insert_TNode(root, p);
    }
}

void Create_Tree_From_Random(TNode *&root, int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        item_type x = rand() % 100;
        TNode *p = Create_TNode(x);
        Insert_TNode(root, p);
    }
}

//Duyet cay theo 6 cach
void Traverse_NLR(TNode *root)
{
    if (root == NULL)
        return;
    
    printf("%d ", root->data);
    Traverse_NLR(root->left);
    Traverse_NLR(root->right);
}

void Traverse_LNR(TNode *root)
{
    if (root == NULL)
        return;
    
    Traverse_LNR(root->left);
    printf("%d ", root->data);
    Traverse_LNR(root->right);
}

void Traverse_LRN(TNode *root)
{
    if (root == NULL)
        return;
    
    Traverse_LRN(root->left);
    Traverse_LRN(root->right);
    printf("%d ", root->data);
}

void Traverse_NRL(TNode *root)
{
    if (root == NULL)
        return;
    
    printf("%d ", root->data);
    Traverse_NRL(root->right);
    Traverse_NRL(root->left);
}

void Traverse_RNL(TNode *root)
{
    if (root == NULL)
        return;
    
    Traverse_RNL(root->right);
    printf("%d ", root->data);
    Traverse_RNL(root->left);
}

void Traverse_RLN(TNode *root)
{
    if (root == NULL)
        return;
    
    Traverse_RLN(root->right);
    Traverse_RLN(root->left);
    printf("%d ", root->data);
}

TNode *find_TNode(TNode *root, item_type x)
{
    if (root == NULL)
        return NULL;
    
    if (root->data == x)
        return root;
    else if (root->data > x)
        return find_TNode(root->left, x);
    else
        return find_TNode(root->right, x);
}

TNode *findReplace(TNode *p)
{
    TNode *f = p;
    TNode *q = p->right;

    while (q->left != NULL)
    {
        f = q;
        q = q->left;
    }

    p->data = q->data;

    if (f == p)
        f->right = q->right;
    else
        f->left = q->right;

    return q;
}

int Delete_TNode(TNode *&root, item_type x)
{
    if (root == NULL)
        return 0;
    
    if (root->data > x)
        Delete_TNode(root->left, x);
    else if (root->data < x)
        Delete_TNode(root->right, x);
    else
    {
        TNode *p = root;
        if (root->left == NULL)
            root = root->right;
        else if (root->right == NULL)
            root = root->left;
        else
            p = findReplace(p);

        delete p;
        return 1;
    }
}

void Delete_Tree(TNode *&root)
{
    if (root == NULL)
        return;
    
    Delete_Tree(root->left);
    Delete_Tree(root->right);
    delete root;
}

int Count_TNode_Bigger_x(TNode *root, item_type x)
{
    if (root == NULL)
        return 0;
    
    int left = Count_TNode_Bigger_x(root->left, x);
    int right = Count_TNode_Bigger_x(root->right, x);

    if (root->data > x)
        return left + right + 1;
    else
        return left + right;
}

int Count_TNode_Smaller_x(TNode *root, item_type x)
{
    if (root == NULL)
        return 0;
    
    int left = Count_TNode_Smaller_x(root->left, x);
    int right = Count_TNode_Smaller_x(root->right, x);

    if (root->data < x)
        return left + right + 1;
    else
        return left + right;
}

int Count_TNode_in_Range(TNode *root, item_type x, item_type y)
{
    if (root == NULL)
        return 0;
    
    int left = Count_TNode_in_Range(root->left, x, y);
    int right = Count_TNode_in_Range(root->right, x, y);

    if (root->data >= x && root->data <= y)
        return left + right + 1;
    else
        return left + right;
}

TNode *findMax(TNode *root)
{
    if (root == NULL)
        return NULL;
    
    TNode *p = root;
    while (p->right != NULL)
        p = p->right;
    
    return p;
}

TNode *findMin(TNode *root)
{
    if (root == NULL)
        return NULL;
    
    TNode *p = root;
    while (p->left != NULL)
        p = p->left;
    
    return p;
}

int Height_Tree(TNode *root)
{
    if (root == NULL)
        return 0;
    
    int left = Height_Tree(root->left);
    int right = Height_Tree(root->right);

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

void Xuat_Node_o_muc_k(TNode *root, int k, int i)
{
    if (root != NULL)
    {
        if (i == k)
            printf("%d ", root->data);

        Xuat_Node_o_muc_k(root->left, k, i + 1);
        Xuat_Node_o_muc_k(root->right, k, i + 1);
    }
}

void Xuat_Node_la_o_muc_k(TNode *root, int k, int i)
{
    if (root != NULL)
    {
        if (i == k && root->left == NULL && root->right == NULL)
            printf("%d ", root->data);

        Xuat_Node_la_o_muc_k(root->left, k, i + 1);
        Xuat_Node_la_o_muc_k(root->right, k, i + 1);
    }
}

void Xuat_Node_co_1_con_o_muc_k(TNode *root, int k, int i)
{
    if (root != NULL)
    {
        if (i == k && 
        ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)))
            printf("%d ", root->data);

        Xuat_Node_co_1_con_o_muc_k(root->left, k, i + 1);
        Xuat_Node_co_1_con_o_muc_k(root->right, k, i + 1);
    }
}

void Xuat_Node_co_2_con_o_muc_k(TNode *root, int k, int i)
{
    if (root != NULL)
    {
        if (i == k && root->left != NULL && root->right != NULL)
            printf("%d ", root->data);

        Xuat_Node_co_2_con_o_muc_k(root->left, k, i + 1);
        Xuat_Node_co_2_con_o_muc_k(root->right, k, i + 1);
    }
}

//Kiểm tra node có ở mức k hay không
int Check_Node_o_muc_k(TNode *root, item_type x, int k, int i)
{
    if (root == NULL)
        return 0;
    
    if (root->data == x && i == k)
        return 1;
    
    return Check_Node_o_muc_k(root->left, x, k, i + 1) || Check_Node_o_muc_k(root->right, x, k, i + 1);
}

int Dem_Node_o_muc_k(TNode *root, int k, int i)
{
    if (root == NULL)
        return 0;
    
    if (i == k)
        return 1;

    return Dem_Node_o_muc_k(root->left, k, i + 1) + Dem_Node_o_muc_k(root->right, k, i + 1);
}

int Dem_Node_la_o_muc_k(TNode *root, int k, int i)
{
    if (root == NULL)
        return 0;
    
    if (i == k && root->left == NULL && root->right == NULL)
        return 1;

    return Dem_Node_la_o_muc_k(root->left, k, i + 1) + Dem_Node_la_o_muc_k(root->right, k, i + 1);
}

int Dem_Node_co_1_con_o_muc_k(TNode *root, int k, int i)
{
    if (root == NULL)
        return 0;
    
    if (i == k && 
    ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)))
        return 1;

    return Dem_Node_co_1_con_o_muc_k(root->left, k, i + 1) + Dem_Node_co_1_con_o_muc_k(root->right, k, i + 1);
}

int Dem_Node_co_2_con_o_muc_k(TNode *root, int k, int i)
{
    if (root == NULL)
        return 0;
    
    if (i == k && root->left != NULL && root->right != NULL)
        return 1;
    
    return Dem_Node_co_2_con_o_muc_k(root->left, k, i + 1) + Dem_Node_co_2_con_o_muc_k(root->right, k, i + 1);
}

//Tổng các node có giá trị dương 
item_type Sum_TNode_positive(TNode *root)
{
    if (root == NULL)
        return 0;
    
    if (root->data > 0)
        return Sum_TNode_positive(root->left) + Sum_TNode_positive(root->right) + root->data;
    else
        return Sum_TNode_positive(root->left) + Sum_TNode_positive(root->right);
}

//Tổng các node có giá trị âm
item_type Sum_TNode_negative(TNode *root)
{
    if (root == NULL)
        return 0;
    
    if (root->data < 0)
        return Sum_TNode_negative(root->left) + Sum_TNode_negative(root->right) + root->data;
    else
        return Sum_TNode_negative(root->left) + Sum_TNode_negative(root->right);
}

void Tao_cay(TNode *&root)
{
    printf("\n\t========== Tao cay ==========");
    printf("\n1. Tao cay tu mamg");
    printf("\n2. Tao cay tu du lieu nhap tu ban phim");
    printf("\n3. Tao cay ngau nhien");

    printf("\nNhap lua chon: ");
    int luachon;
    scanf("%d", &luachon);

    switch (luachon)
    {
        case 1:
        {
            int a[100];
            int n;
            printf("\nNhap so luong phan tu: ");
            scanf("%d", &n);

            for (int i = 0; i < n; i++)
            {
                printf("\nNhap phan tu thu %d: ", i + 1);
                scanf("%d", &a[i]);
            }

            Create_Tree_From_Array(root, a, n);
            break;
        }
        case 2:
        {
            int n;
            printf("\nNhap so luong phan tu: ");
            scanf("%d", &n);

            Create_Tree_From_KeyBoard(root, n);
            break;
        }
        case 3:
        {
            int n;
            printf("\nNhap so luong phan tu: ");
            scanf("%d", &n);

            Create_Tree_From_Random(root, n);
            break;
        }
        default:
        {
            printf("\nLua chon khong hop le!");
            break;
        }
    }
}

void Xuat_cay(TNode *root)
{
    printf("\n\t========== Xuat cay ==========");
    printf("\n1. Xuat cay theo NLR");
    printf("\n2. Xuat cay theo LNR");
    printf("\n3. Xuat cay theo LRN");
    printf("\n4. Xuat cay theo NRL");
    printf("\n5. Xuat cay theo RNL");
    printf("\n6. Xuat cay theo RLN");

    printf("\nNhap lua chon: ");
    int luachon;
    scanf("%d", &luachon);

    switch (luachon)
    {
        case 1:
        {
            printf("\nCay theo NLR: ");
            Traverse_NLR(root);
            break;
        }
        case 2:
        {
            printf("\nCay theo LNR: ");
            Traverse_LNR(root);
            break;
        }
        case 3:
        {
            printf("\nCay theo LRN: ");
            Traverse_LRN(root);
            break;
        }
        case 4:
        {
            printf("\nCay theo NRL: ");
            Traverse_NRL(root);
            break;
        }
        case 5:
        {
            printf("\nCay theo RNL: ");
            Traverse_RNL(root);
            break;
        }
        case 6:
        {
            printf("\nCay theo RLN: ");
            Traverse_RLN(root);
            break;
        }
        default:
        {
            printf("\nLua chon khong hop le!");
            break;
        }
    }
}

void Xuat_cac_node_muc_k(TNode *root)
{
    printf("\n\t========== Xuat cac node muc k ==========");
    printf("\n1. Xuat cac node muc k");
    printf("\n2. Xuat cac node la muc k");
    printf("\n3. Xuat cac node o muc k co 1 con");
    printf("\n4. Xuat cac node o muc k co 2 con");

    printf("\nNhap lua chon: ");
    int luachon;
    scanf("%d", &luachon);


    int k;
    printf("\nNhap muc k: ");
    scanf("%d", &k);

    switch(luachon)
    {
        case 1:
        {
            printf("\nCac node o muc %d: ", k);
            Xuat_Node_o_muc_k(root, k, 0);
            break;
        }
        case 2:
        {
            printf("\nCac node la o muc %d: ", k);
            Xuat_Node_la_o_muc_k(root, k, 0);
            break;
        }
        case 3:
        {
            printf("\nCac node o muc %d co 1 con: ", k);
            Xuat_Node_co_1_con_o_muc_k(root, k, 0);
            break;
        }
        case 4:
        {
            printf("\nCac node o muc %d co 2 con: ", k);
            Xuat_Node_co_2_con_o_muc_k(root, k, 0);
            break;
        }
        default:
        {
            printf("\nLua chon khong hop le!");
            break;
        }
    }
}

void Dem_cac_node_muc_k(TNode *root)
{
    printf("\n\t========== Dem cac node muc k ==========");
    printf("\n1. Dem cac node muc k");
    printf("\n2. Dem cac node la muc k");
    printf("\n3. Dem cac node o muc k co 1 con");
    printf("\n4. Dem cac node o muc k co 2 con");

    printf("\nNhap lua chon: ");
    int luachon;
    scanf("%d", &luachon);


    int k;
    printf("\nNhap muc k: ");
    scanf("%d", &k);

    switch(luachon)
    {
        case 1:
        {
            printf("\nSo node o muc %d: %d", k, Dem_Node_o_muc_k(root, k, 0));
            break;
        }
        case 2:
        {
            printf("\nSo node la o muc %d: %d", k, Dem_Node_la_o_muc_k(root, k, 0));
            break;
        }
        case 3:
        {
            printf("\nSo node o muc %d co 1 con: %d", k, Dem_Node_co_1_con_o_muc_k(root, k, 0));
            break;
        }
        case 4:
        {
            printf("\nSo node o muc %d co 2 con: %d", k, Dem_Node_co_2_con_o_muc_k(root, k,0));
            break;
        }
        default:
        {
            printf("\nLua chon khong hop le!");
            break;
        }
    }
}

void MENU(Tree &t)
{
    while (1 != 0)
    {
        system("cls");
        printf("\n\n\t================= MENU =================");
        printf("\n1.  Tao cay");
        printf("\n2.  Xuat cay");
        printf("\n3.  Them node vao cay");
        printf("\n4.  Tim node co gia tri x");
        printf("\n5.  Xoa node co gia tri x");
        printf("\n6.  Xuat toan bo cay theo thu tu giam dan");
        printf("\n7.  Node co gia tri nho nhat");
        printf("\n8.  Node co gia tri lon nhat");
        printf("\n9.  Xuat cac node o muc k");
        printf("\n10. Dem cac node o muc k");
        printf("\n11. Kiem tra node co phai la node o muc k");
        printf("\n0.  Thoat chuong trinh");
        printf("\n\t================= END =================");

        int luachon;
        printf("\nNhap lua chon: ");
        scanf("%d", &luachon);

        switch(luachon)
        {
            case 1:
            {
                Tao_cay(t.root);
                system("pause");
                break;
            }
            case 2:
            {
                Xuat_cay(t.root);
                system("pause");
                break;
            }
            case 3:
            {
                int x;
                printf("\nNhap gia tri node can them: ");
                scanf("%d", &x);

                TNode *p = Create_TNode(x);
                if (Insert_TNode(t.root, p) == 0)
                {
                    printf("\nThem node khong thanh cong!");
                }
                else
                {
                    printf("\nThem node thanh cong!");
                }
                printf("\n");
                system("pause");
                break;
            }
            case 4:
            {
                int x;
                printf("\nNhap gia tri node can tim: ");
                scanf("%d", &x);

                TNode *p = find_TNode(t.root, x);
                if (p == NULL)
                {
                    printf("\nKhong tim thay node co gia tri %d", x);
                }
                else
                {
                    printf("\nTim thay node co gia tri %d", x);
                }
                system("pause");
                break;
            }
            case 5:
            {
                int x;
                printf("\nNhap gia tri node can xoa: ");
                scanf("%d", &x);

                if (Delete_TNode(t.root, x) == 0)
                {
                    printf("\nXoa node khong thanh cong!");
                }
                else
                {
                    printf("\nXoa node thanh cong!");
                }
                printf("\n");
                system("pause");
                break;
            }
            case 6:
            {
                printf("\nCay theo thu tu giam dan: ");
                Traverse_RNL(t.root);
                system("pause");
                break;
            }
            case 7:
            {
                TNode *p = findMin(t.root);
                printf("\nNode co gia tri nho nhat: %d", p->data);
                system("pause");
                break;
            }
            case 8:
            {
                TNode *p = findMax(t.root);
                printf("\nNode co gia tri lon nhat: %d", p->data);
                system("pause");
                break;
            }
            case 9:
            {
                Xuat_cac_node_muc_k(t.root);
                system("pause");
                break;
            }
            case 10:
            {
                Dem_cac_node_muc_k(t.root);
                system("pause");
                break;
            }
            case 11:
            {
                int x;
                printf("\nNhap gia tri node can kiem tra: ");
                scanf("%d", &x);

                int check = 0;
                int k = 0;
                for (int i = 0; i < Height_Tree(t.root); i++)
                {
                    if (Check_Node_o_muc_k(t.root, x, i, 0) == 1)
                    {
                        check = 1;
                        k = i;
                    }
                }

                if (check == 1)
                {
                    printf("\nNode co gia tri %d la node o muc %d", x, k);
                }
                else
                {
                    printf("\nNode co gia tri %d khong ton tai", x);
                }
                system("pause");
                break;
            }
            case 0: return;
                break;
        }
    }
}

int main()
{
    Tree t;
    t.root = NULL;

    MENU(t);

    return 0;
}