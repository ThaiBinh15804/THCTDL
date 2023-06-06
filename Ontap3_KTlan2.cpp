#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

struct Dienthoai
{
    char maDT[30];
    char tenDT[30];
    int khuyenmai;
    float dongia;
    int slg;
};

typedef Dienthoai value;

struct Node
{
    value data;
    Node *left;
    Node *right;
};

struct Tree
{
    Node *root;
};

void Init(Tree &t)
{
    t.root = NULL;
}

Node *createNode(value x)
{
    Node *p = new Node;
    if (p == NULL)
    {
        printf("\nKhong du bo nho cap phat");
        return NULL;
    }

    p->data = x;
    p->left = NULL;
    p->right = NULL;

    return p;
}

void addNode(Node *&root, Node *p)
{
    if (p == NULL)
        return;

    if (root == NULL)
    {
        root = p;
        return;
    }
    else
    {
        if (root->data.dongia > p->data.dongia)
            addNode(root->left, p);
        else if (root->data.dongia < p->data.dongia)
            addNode(root->right, p);
    }
}

Node *findNode_replace(Node *p)
{
    Node *f = p;
    Node *q = p->right;

    while (q->left != NULL)
    {
        f = q;
        q = q->left;
    }

    p->data = q->data;
    if (f == q)
        f->right = q->right;
    else
        f->left = q->right;

    return q;
}

void deleteNode(Node *&root, value x)
{
    if (root == NULL)
        return ;
    
    if (root->data.dongia == x.dongia)
    {
        Node *p = root;
        if (root->left == NULL)
            root = root->right;
        else if (root->right == NULL)
            root = root->left;
        else
            p = findNode_replace(root);

        delete p;
        return ;
    }
    if (root->data.dongia > x.dongia)
        deleteNode(root->left, x);
    else    
        deleteNode(root->right, x);
}

void Nhap(value &x)
{
    fflush(stdin);
    printf("\n\tNhap ma DT: ");
    scanf("%s", x.maDT);
    printf("\n\tNhap ten DT: ");
    scanf("%s", x.tenDT);
    printf("\n\tNhap khuyen mai: ");
    scanf("%d", &x.khuyenmai);
    printf("\n\tNhap don gia: ");
    scanf("%f", &x.dongia);
    printf("\n\tNhap so luong: ");
    scanf("%d", &x.slg);
}

void Xuat(value x)
{
    printf("\n%-20s|%-20s|%-15d|%-25.2f|%-15d", x.maDT, x.tenDT, x.khuyenmai, x.dongia, x.slg);
}

void Nhap_Tree(Tree &t)
{
    int n;
    printf("\nNhap so luong muon them: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i ++)
    {
        value x;
        printf("\n----------- Nhap thong tin dien thoai thu %d -----------", i);
        Nhap(x);
        Node *p = createNode(x);
        addNode(t.root, p);
    }
}

void Xuat_Tree(Node *root)
{
    if (root == NULL)
        return ;
    
    Xuat(root->data);
    Xuat_Tree(root->left);
    Xuat_Tree(root->right);
}

void findNode_khuyenmai_hon_x(Node *root, int x)
{
    if (root == NULL)
        return ;
    
    if (root->data.khuyenmai > x)
        Xuat(root->data);
    findNode_khuyenmai_hon_x(root->left, x);
    findNode_khuyenmai_hon_x(root->right, x);
}

Node *findMax_dongia(Tree t)
{
    Node *p = t.root;
    Node *max = p;
    while (p != NULL)
    {
        if (max->data.dongia < p->data.dongia)
            max = p;
        p = p->right;
    }

    return max;
}

float tien_khuyenmai(value x)
{
    int tien_KM = x.dongia * float(x.khuyenmai) /100;
    return tien_KM;
}

float tong_Tien_all_theo_dongia_real(Node *root)
{
    if (root == NULL)
        return 0;
    
    float dongia_real = root->data.dongia - tien_khuyenmai(root->data);
    return dongia_real + tong_Tien_all_theo_dongia_real(root->left) + tong_Tien_all_theo_dongia_real(root->right);
}

void Xuat_DT_dongia_real(Node *root)
{
    if (root == NULL)
        return;
    
    value x = root->data;
    x.dongia = x.dongia - tien_khuyenmai(x);
    Xuat(x);
    Xuat_DT_dongia_real(root->left);
    Xuat_DT_dongia_real(root->right);
}

float tongTien_giam(value x)
{
    return tien_khuyenmai(x) *x.slg;
}

void Xuat_DT_tongTien_giam(Node *root, int i)
{
    if (root == NULL)
        return ;
    
    printf("\n%-20s|%-20s|%-25.2f", root->data.maDT, root->data.tenDT, tongTien_giam(root->data));

    Xuat_DT_tongTien_giam(root->left, i);
    Xuat_DT_tongTien_giam(root->right, i);
}

void Xuat_Tree_giam(Node *root)
{
    if (root == NULL)
        return;
    Xuat_Tree_giam(root->right);
    Xuat(root->data);
    Xuat_Tree_giam(root->left);
}

int Height_root(Node *root)
{
    if (root == NULL)
        return 0;

    int left = Height_root(root->left);
    int right = Height_root(root->right);

    if (left > right)
        return left + 1;
    return right + 1;
}

void Height_root_slg_hon_10(Node *root)
{
    if (root == NULL)
        return;
    
    if (root->data.slg > 10)
        printf("\n%-20s|%-20s|%-15d|%-25.2f|%-15d|%-10d", root->data.maDT, root->data.tenDT, root->data.khuyenmai, root->data.dongia, root->data.slg, Height_root(root));
    Height_root_slg_hon_10(root->left);
    Height_root_slg_hon_10(root->right);
}

int Cout_DT_2con_dongia_5000(Node *root)
{
    if (root == NULL)
        return 0;
    
    if (root->left != NULL && root->right != NULL)
    {
        if (root->left->data.dongia > 5000 && root->right->data.dongia > 5000)
            return 1 + Cout_DT_2con_dongia_5000(root->left) + Cout_DT_2con_dongia_5000(root->right);
    }
    else    
        return Cout_DT_2con_dongia_5000(root->left) + Cout_DT_2con_dongia_5000(root->right);
}

void Xuat_DT_muc_k(Node *root, int k, int i)
{
    if (root == NULL)
        return;
    if (i == k)
        Xuat(root->data);
    Xuat_DT_muc_k(root->left, k, i + 1);
    Xuat_DT_muc_k(root->right, k, i + 1);
}

void delete_DT_tenDT(Node *&root, char ten[], int &ktra)
{
    if (root == NULL)
        return;
    
    delete_DT_tenDT(root->left, ten, ktra);
    delete_DT_tenDT(root->right, ten, ktra);
    if (strcmp(root->data.maDT, ten) == 0)
    {
        deleteNode(root, root->data);
        ktra = 1;
    }
    
}

void MENU(Tree &t)
{
    while (1!=0)
    {
        system("cls");
        printf("\n\n============= MENU =============");
        printf("\n\n1.  Nhap danh sach dien thoai");
        printf("\n2.  Xuat danh sach dien thoai");
        printf("\n3.  Dien thoai co khuyen mai tren 10%");
        printf("\n4.  Dien thoai co don gia lon nhat");
        printf("\n5.  Tong tien tat ca dien thoai theo don gia thuc te");
        printf("\n6.  Xuat dien thoai co gia ban thuc te sau khi tru khuyen mai");
        printf("\n7.  Xuat tong tien giam cua dien thoai");
        printf("\n8.  Xuat danh sach giam dan theo don gia");
        printf("\n9.  Chieu cao cay voi goc la node co slg lon hon 10");
        printf("\n10. Dem so DT co 2 con ma don gia cua 2 con lon hon 5000");
        printf("\n11. Xuat cac dien thoai o muc k");
        printf("\n12. Xoa cac dien thoai co ten trung voi ten nhap vao");
        printf("\n0. Thoat");
        printf("\n\n================================");
    

    int lc;
    printf("\nNhap vao lua chon: ");
    scanf("%d", &lc);

    switch(lc)
    {
        case 1: 
        {
            Nhap_Tree(t);
            break;
        }
        case 2:
        {
            printf("\n\n%-20s|%-20s|%-15s|%-25s|%-15s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong");
            Xuat_Tree(t.root);
            _getch();
            break;
        }
        case 3:
        {
            printf("\n\n-------- Thong tin cac dien thoai co khuyen mai lon hon 10 --------");
            printf("\n\n%-20s|%-20s|%-15s|%-25s|%-15s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong");
            findNode_khuyenmai_hon_x(t.root, 10);
            _getch();
            break;
        }
        case 4:
        {
            Node *max = findMax_dongia(t);
            if (max == NULL)
                printf("\nCay rong!");
            else
            {
                printf("\n------- Thong tin dien thoai co don gia lon nhat -------");
                printf("\n\n%-20s|%-20s|%-15s|%-25s|%-15s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong");
                Xuat(max->data);
            }
            _getch();
            break;
        }
        case 5:
        {
            printf("\n\nTong tien tat ca dien thoai theo don gia thuc te: %.2f", tong_Tien_all_theo_dongia_real(t.root));
            _getch();
            break;
        }
        case 6:
        {
            printf("\n------------ Gia ban thuc te cua dien thoai sau khi tru khuyen mai ------------");
            printf("\n\n%-20s|%-20s|%-15s|%-25s|%-15s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong");
            Xuat_DT_dongia_real(t.root);
            _getch();
            break;
        }
        case 7:
        {
            printf("\n------------ Tong tien giam cua danh sach cac dien thoai ------------");
            printf("\n\n%-20s|%-20s|%-35s", "Ma DT", "Ten DT", "Tong tien giam gia");
            Xuat_DT_tongTien_giam(t.root, 1);
            _getch();
            break;
        }
        case 8:
        {
            printf("\n------------ Danh sach giam dan theo don gia ------------");
            printf("\n\n%-20s|%-20s|%-15s|%-25s|%-15s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong");
            Xuat_Tree_giam(t.root);
            _getch();
            break;
        }
        case 9:
        {
            printf("\n---- Thong tin dien thoai co so luong lon hon 10 va chieu cao cay tinh tu node do ----");
            printf("\n\n%-20s|%-20s|%-15s|%-25s|%-15s|%-10s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong", "Chieu cao cay");
            Height_root_slg_hon_10(t.root);
            _getch();
            break;
        }
        case 10:
        {
            printf("\n\nSo luong dien thoai co 2 con trong do don gia cua 2 con lon hon 5000 la: %d", Cout_DT_2con_dongia_5000(t.root));
            _getch();
            break;
        }
        case 11:
        {
            int k;
            printf("\nNhap vao muc k: ");
            scanf("%d", &k);
            
            printf("\n\n------------ Danh sach cac dien thoai o muc %d ------------", k);
            printf("\n\n%-20s|%-20s|%-15s|%-25s|%-15s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong");
            Xuat_DT_muc_k(t.root, k, 0);
            _getch();
            break;
        }
        case 12:
        {
            char ten[30];
            printf("\nNhap vao ten DT muon xoa: ");
            scanf("%s", ten);
            int ktra = 0;
            delete_DT_tenDT(t.root, ten, ktra);
            if (ktra == 0)
                printf("\nKhong co DT nao trung ten!");
            else
                printf("\nDa xoa thanh cong!");
            _getch();
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
    Init(t);
    MENU(t);
    return 0;
}
