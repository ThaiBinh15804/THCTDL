#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct Dienthoai
{
    char maDT[31];
    char tenDT[31];
    int khuyenmai;
    float dongia;
    int slg;
};

struct Node
{
    Dienthoai data;
    Node *next;
};

struct List
{
    Node *head;
    Node *tail;
};

void Init(List &l)
{
    l.head = l.tail = NULL;
}

Node *createNode(Dienthoai x)
{
    Node *p = new Node;
    if(p == NULL)
        return NULL;
    p->data = x;
    p->next = NULL;
    return p;
}

void addTail(List &l, Node *p)
{
    if(l.head == NULL)
        l.head = l.tail = p;
    else
    {
        l.tail->next = p;
        l.tail = p;
    }
}

int isEmpty(List l)
{
    if(l.head == NULL)
        return 1;
    return 0;
}

void nhap(Dienthoai &x)
{
    fflush(stdin);
    printf("\nNhap ma dien thoai: ");
    scanf("%s", &x.maDT);
    printf("\nNhap ten dien thoai: ");
    scanf("%s", &x.tenDT);
    printf("\nNhap khuyen mai: ");
    scanf("%d", &x.khuyenmai);
    printf("\nNhap don gia: ");
    scanf("%f", &x.dongia);
    printf("\nNhap so luong: ");
    scanf("%d", &x.slg);
}

void nhapDS(List &l)
{
    int n;
    printf("\nNhap so luong dien thoai: ");
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        Dienthoai x;
        printf("\n---- Nhap thong tin dien thoai thu %d ----\n", i);
        nhap(x);
        Node *p = createNode(x);
        addTail(l, p);
    }
}

void xuat(Dienthoai x)
{
    printf("\nMa dien thoai: %s", x.maDT);
    printf("\nTen dien thoai: %s", x.tenDT);
    printf("\nKhuyen mai: %d", x.khuyenmai);
    printf("\nDon gia: %.2f", x.dongia);
    printf("\nSo luong: %d", x.slg);
}

void xuat_theo_hang(Dienthoai x)
{
    printf("\n%-15s %-15s %-15d %-15.2f %-15d", x.maDT, x.tenDT, x.khuyenmai, x.dongia, x.slg);
}

//Hàm xuất danh sách theo dạng bảng
void xuatDS(List l)
{
    if(isEmpty(l) == 1)
        printf("\nDanh sach rong!");
    else
    {
        printf("\n%-15s %-15s %-15s %-15s %-15s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong");
        for(Node *k = l.head; k != NULL; k = k->next)
        {
            printf("\n%-15s %-15s %-15d %-15.2f %-15d", k->data.maDT, 
                    k->data.tenDT, k->data.khuyenmai, k->data.dongia, k->data.slg);
        }
    }
}

List find_Node_khuyenmai_lonhon_x(List l, int x)
{
    List kq;
    Init(kq);
    for(Node *p = l.head; p != NULL; p = p->next)
    {
        if(p->data.khuyenmai > x)
        {
            Dienthoai y = p->data;
            Node *q = createNode(y);
            addTail(kq, q);
        }
    }
    return kq;
}

float tinh_tiengiam(Dienthoai &x)
{
    return float(x.dongia * x.khuyenmai / 100);
}

void Giaban_real(List &l)
{
    printf("\n%-15s %-15s %-15s %-15s %-15s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong");
    for (Node *k = l.head; k != NULL; k = k->next)
    {
        Dienthoai x = k->data;
        x.dongia = x.dongia - tinh_tiengiam(x);
        xuat_theo_hang(x);
    }
}

float tong_tien_giamgia(Dienthoai x)
{
    float tmp = x.dongia * x.slg;
    return float(tmp - (tmp * x.khuyenmai / 100));
}

void Tongtien_giamgia_list(List l)
{
    printf("\n\n------- Tong tien giam gia cua dien thoai trong danh sach -------");
    int dem = 0;
    if (isEmpty(l) == 1)
    {
        printf("\nDanh sach rong!");
        return;
    }
    for (Node *k = l.head; k != NULL; k = k->next)
    {
        printf("\n\nTen dien thoai thu %d: %s", ++dem, k->data.tenDT);
        printf("\nTong tien giam gia: %.2f", tong_tien_giamgia(k->data));
    }
}

void swap(Dienthoai &x, Dienthoai &y)
{
    Dienthoai tmp = x;
    x = y;
    y = tmp;
}

void SX_list_giamdan_dongia(List &l)
{
    for (Node *k = l.head; k != NULL; k = k->next)
    {
        for (Node *h = k->next; h != NULL; h = h->next)
        {
            if (k->data.dongia < h->data.dongia)
            {
                swap(k->data, h->data);
            }
        }
    }
}

void add_saocho_thutu_giam(List &l, Node *p)
{
   SX_list_giamdan_dongia(l);
   for (Node *k = l.head; k != NULL; k = k->next)
   {
        Node *h = k->next;
        if (h != NULL)
        {
            if (p->data.dongia < k->data.dongia && p->data.dongia > h->data.dongia)
            {
                p->next = h;
                k->next = p;
                return;
            }
        }
   } 
}

Node *find_dongia_max(List l)
{
    if (isEmpty(l) == 1)
    {
        printf("\nDanh sach rong!");
        return NULL;
    }
    Node *max = l.head;
    for (Node *k = l.head; k != NULL; k = k->next)
    {
        if (k->data.dongia > max->data.dongia)
        {
            max = k;
        }
    }

    return max;
}

void Xuat_hoadon_max(List l)
{
    Node *max = find_dongia_max(l);
    printf("\n\n------- Hoa don co don gia cao nhat -------");
    printf("\n%-15s %-15s %-15s %-15s %-15s", "Ma DT", "Ten DT", "Khuyen mai", "Don gia", "So luong");
    for (Node *k = l.head; k != NULL; k = k->next)
    {
        if (k->data.dongia == max->data.dongia)
        {
            xuat_theo_hang(k->data);
        }
    }
}

Node *findNode(List l, char x[])
{
    if (isEmpty(l) == 1)
    {
        return NULL;
    }
    
    for (Node *k = l.head; k != NULL; k = k->next)
    {
        if (strcmp(k->data.maDT, x) == 0)
        {
            return k;
        }
    }
}

void Xoa_dau(List &l)
{
    if (isEmpty(l) == 1)
    {
        printf("\nDanh sach rong!");
        return;
    }

    if (l.head == l.tail)
    {
        delete l.head;
        l.head = l.tail = NULL;
        return;
    }

    Node *p = l.head;
    l.head = l.head->next;
    delete p;
}

void Xoa_sau(List &l, Node *p)
{
    if (isEmpty(l) == 1)
    {
        printf("\nDanh sach rong!");
        return;
    }

    if (p == l.tail)
    {
        printf("\nKhong the xoa!");
        return;
    }

    Node *q = p->next;
    p->next = q->next;
    delete q;
}

void Xoa_cuoi(List &l)
{
    if (isEmpty(l) == 1)
    {
        printf("\nDanh sach rong!");
        return;
    }

    if (l.head == l.tail)
    {
        delete l.head;
        l.head = l.tail = NULL;
        return;
    }

    for (Node *k = l.head; k != NULL; k = k->next)
    {
        if (k->next == l.tail)
        {
            Node *p = k->next;
            k->next = NULL;
            l.tail = k;
            delete p;
            return;
        }
    }
}

void Xoa_X_theo_maDT(List &l, char x[])
{
    Node *p = findNode(l, x);
    if (p == NULL)
    {
        printf("\nKhong tim thay!");
        return;
    }

    if (p == l.head)
    {
        Xoa_dau(l);
        printf("\nDa xoa!");
        return;
    }

    if (p == l.tail)
    {
        Xoa_cuoi(l);
        printf("\nDa xoa!");
        return;
    }

    for (Node *k = l.head; k != NULL; k = k->next)
    {
        if (k->next == p)
        {
            Xoa_sau(l, k);
            printf("\nDa xoa!");
            return;
        }
    }
}

void Xoa_DT_trung(List &l)
{
    int dem = 0;
    for (Node *k = l.head; k != NULL; k = k->next)
    {
        for (Node *h = k->next; h != NULL; h = h->next)
        {
            if (strcmp(k->data.maDT, h->data.maDT) == 0 && strcmp(k->data.tenDT, h->data.tenDT) == 0 
            && k->data.khuyenmai == h->data.khuyenmai && k->data.dongia == h->data.dongia)
            {
                k->data.slg += h->data.slg;
                dem++;
                if (h == l.tail)
                {
                    Xoa_cuoi(l);
                    printf("\nDa xoa!");
                    break;
                }
                
                Xoa_sau(l, k);
                printf("\nDa xoa!");
            }
        }
    }

    if (dem == 0)
    {
        printf("\nKhong co dien thoai trung!");
    }
}

void MENU(List &l)
{
    while (1!=0)
    {
        printf("\n\n============ MENU ============\n");
        printf("\n1. Nhap danh sach dien thoai");
        printf("\n2. Xuat danh sach dien thoai");
        printf("\n3. Cac dien thoai co khuyen mai lon hon 10");
        printf("\n4. Gia ban thuc te cua cac dien thoai");
        printf("\n5. Tong tien giam gia cua cac dien thoai");
        printf("\n6. Sap xep danh sach giam dan theo don gia");
        printf("\n7. Them dien thoai vao danh sach sao cho van giam theo don gia");
        printf("\n8. Dien thoai co don gia lon nhat");
        printf("\n9. Xoa dien thoai theo ma dien thoai");
        printf("\n10. Xoa cac dien thoai trung nhau");
        printf("\n0. Thoat");
        printf("\n\n============ END ============");

        int luachon;
        printf("\nNhap lua chon: ");
        scanf("%d", &luachon);

        switch (luachon)
        {
            case 1:
                nhapDS(l);
                break;
            case 2:
            {
                xuatDS(l);
                _getch();
                break;
            }
            case 3:
            {
                List kq = find_Node_khuyenmai_lonhon_x(l, 10);
                printf("\n\n-------- Danh sach dien thoai co khuyen mai lon hon 10 --------\n");
                if (isEmpty(kq) == 1)
                    printf("\nKhong co dien thoai nao co khuyen mai lon hon 10");
                else
                    xuatDS(kq);

                _getch();
                break;
            }
            case 4:
            {
                printf("\n\n-------- Danh sach dien thoai sau khi giam gia --------\n");
                if (isEmpty(l) == 1)
                    printf("\nDanh sach rong!");
                else
                    Giaban_real(l);
                _getch();
                break;
            }
            case 5:
            {
                Tongtien_giamgia_list(l);
                _getch();
                break;
            }
            case 6:
            {
                printf("\n\n-------- Danh sach dien thoai sau khi sap xep --------\n");
                if (isEmpty(l) == 1)
                    printf("\nDanh sach rong!");
                else
                {
                    SX_list_giamdan_dongia(l);
                    xuatDS(l);
                }
                _getch();
                break;
            }
            case 7:
            {
                Dienthoai x;
                nhap(x);
                Node *p = createNode(x);
                add_saocho_thutu_giam(l, p);
                printf("\n\n-------- Danh sach dien thoai sau khi them --------\n");
                xuatDS(l);
                _getch();
                break;
            }
            case 8:
            {
                Xuat_hoadon_max(l);
                _getch();
                break;
            }
            case 9:
            {
                char ma[10];
                printf("\nNhap ma dien thoai can xoa: ");
                fflush(stdin);
                scanf("%s", ma);

                Xoa_X_theo_maDT(l, ma);
                _getch();
                break;
            }
            case 10:
            {
                Xoa_DT_trung(l);
                _getch();
                break;
            }
            case 0:
                return;
                break;
            default:
            {
                printf("\nLua chon khong hop le!");
                _getch();
                break;
            }
        }
    }
}

int main()
{
    List l;
    Init(l);
    MENU(l);
    return 0;
}