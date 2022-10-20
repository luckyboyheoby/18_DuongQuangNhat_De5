#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> 

struct Ngay {
	int ngay, thang, nam;
};
struct Room {
	char id[8];
	char type[15];
	long price;
	Ngay d_hire;
	int days;
	long thanhTien;
};

struct Node {
	Room data;
	Node *link; //dia chi node ke tiep
};

struct List {
	Node *First, *Last;
};

/*-------Prototype--------*/
void xoaXuongDong(char str[]);
void init(List &l);
void nhapDanhSach(List &l, int &n);
long thanhTien(long price, int days); //Nhan vao don gia va so ngay thue
void xuatDanhSach(List l);
void inPhanTuThanhTienNhoNhat();
void xuatFile(List l);
void docFile(List &l);
void insertLast(List &l, Room x);
void addLast(List &l, Node *new_ele);
void inTieuDe();
void sapXepDanhSachTheoTen(List &l);
int suaPhanTuTheoMa(List &l, char id[]);
int xoaPhanTuTheoMa(List &l, char id[]);
void removeFirst(List &l);
Node *timXoa(List l, char x[]);
void removeAfter(List &l, Node *q);
void xuatThanhTienNhoNhat(List l);
/*-------end prototype--------*/

int main() {
	List l;
	init(l);
	int n = 0;
	char id[8];
	int choice = -1;
	
	do {
		printf("\n1. Nhap danh sach n phan tu: ");
		printf("\n2. Xuat danh sach ");
		printf("\n3. In ra man hinh phan tu thanh tien nho nhat");
		printf("\n4. Xuat file");
		printf("\n5. Doc file");
		printf("\n6. Sap xep theo ten");
		printf("\n7. Sua phan tu theo ma");
		printf("\n8. Xoa phan tu theo ma");
		printf("\n0. Thoat");
		printf("\nNhap lua chon: ");
		scanf("%d", &choice);
		system("cls");
		
		switch(choice) {
			case 1:
				nhapDanhSach(l, n);
				break;
			case 2:
				xuatDanhSach(l);
				break;
			case 3:
				xuatThanhTienNhoNhat(l);
				break;
			case 4:
				xuatFile(l);
				break;
			case 5:
				docFile(l);
				break;
			case 6:
				sapXepDanhSachTheoTen(l);
				break;
			case 7:
				printf("Nhap ma: ");
				fflush(stdin);
				fgets(id, sizeof(id), stdin);
				xoaXuongDong(id);
				suaPhanTuTheoMa(l, id);
				break;
			case 8:
				printf("Nhap ma: ");
				fflush(stdin);
				fgets(id, sizeof(id), stdin);
				xoaXuongDong(id);
				xoaPhanTuTheoMa(l, id);
				break;
		}
		
	} while(choice != 0);
	
	return 0;
}

void xoaXuongDong(char str[]) {
	size_t len = strlen(str);

	if(str[len-1]=='\n') {
		str[len-1]='\0';
	}
}

int nhapPhong(List l, Room &x) {

		printf("\nNhap ma phong: ");
		fflush(stdin);
		fgets(x.id, sizeof(x.id), stdin);
		xoaXuongDong(x.id);
		
		printf("\nNhap loai phong: ");
		fflush(stdin);
		fgets(x.type, sizeof(x.type), stdin);
		xoaXuongDong(x.type);
		
		printf("\nNhap don gia: ");
		fflush(stdin);
		scanf("%ld", &x.price);
		
		printf("\nNhap ngay thue: d/d/y ");
		fflush(stdin);
		scanf("%d/%d/%d", &x.d_hire.ngay, &x.d_hire.thang, &x.d_hire.nam);
		
		printf("\nNhap so ngay: ");
		fflush(stdin);
		scanf("%d", &x.days);
		
		x.thanhTien = thanhTien(x.price, x.days);
		
		return 1; //Thanh cong
}

long thanhTien(long price, int days) {
	return price * days;
}

void nhapDanhSach(List &l, int &n) {
	printf("\nNhap so luong n: ");
	scanf("%d", &n);
	int temp = n;
	while(temp > 0) {
		Room x;
		if(nhapPhong(l, x)) insertLast(l, x);
		temp--;
	}
}

void init(List &l) {
	l.First = l.Last = NULL;
}

Node *getNode(Room x) { // Ham nhan vao mot room -> Tao con tro node -> cap bo nho -> gan gia tri -> tra ve 
	Node *p = new Node; //Cap phat bo nho
	if(p == NULL) { //Cap phat that bai
		return NULL;
	}
	p->data = x;
	p->link = NULL;
	
	return p; //Tra ve con tro (tro toi Node)
}

void insertLast(List &l, Room x) {
	Node *new_ele = getNode(x);
	if(new_ele != NULL) {
		addLast(l, new_ele);
	}
}


void addLast(List &l, Node *new_ele) {
	if(l.First == NULL) { //Kiem tra node dau tien = null thi gan dau va cuoi bang new_ele(vi chi co 1 ptu)
		l.First = l.Last = new_ele;
	} else { // Neu list >= 1 p tu ->link tro ve 
		l.Last->link = new_ele;   // gan con tro link cua list last ve new_ele
		l.Last = new_ele;			// gan con tro list last ve new_ele 
	}
}

void xuatPhong(Room x, int &stt) {
	printf("%-5d %-10s %-15s %-d/%-d/%-d%-6s %-12ld %-15d %-8d\n", stt, x.id, x.type, x.d_hire.ngay, x.d_hire.thang, x.d_hire.nam, "", x.price , x.days, x.thanhTien);
	stt = stt + 1;
}

void xuatDanhSach(List l) {
	int stt = 1;
	inTieuDe();
	for(Node *p = l.First; p != NULL; p = p->link) {
		xuatPhong(p->data, stt);
	}
}

void inTieuDe() {
	printf("%-5s %-10s %-15s %-15s %-12s %-15s %-8s\n", "STT", "Ma phong", "Loai phong", "Ngay thue", "Don gia", "So ngay", "Thanh tien");
	for(int i = 1; i <= 100; i++) {
		printf("-");
	}
	printf("\n");
}

void xuatFile(List l) {
	FILE *f = fopen("data.bin", "wb");
	int n = 1;
	if(f == NULL) printf("File error!\n");
	else {
		for(Node *p=l.First; p!=NULL; p=p->link) {
			Room x = p->data;
			Room *q = &x;
			fwrite(q, sizeof(Room), 1, f);
		}
	}
	fclose(f);
	printf("\tDa ghi xuong file thanh cong!\n");
}

void docFile(List &l) {
	FILE *f = fopen("data.bin", "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / sizeof(Room);
	fseek(f, 0, SEEK_SET);
	init(l);
	for(int i = 1; i <= n; i++) {
		Room *x = new Room;
		fread(x, sizeof(Room), 1, f);
		Node *new_ele = getNode(*x);
		if(new_ele != NULL) {
			addLast(l, new_ele);
		}
	}
	fclose(f);
	printf("\t Doc tu file thanh cong!\n");
}

void sapXepDanhSachTheoTen(List &l) {
	for(Node *p = l.First; p != l.Last; p = p->link) {
		for(Node *q=p->link; q!=NULL; q=q->link) {
			if(strcmp(p->data.id, q->data.id) > 0) {
				Room temp = q->data;
				p->data = q->data;
				q->data = temp;
			}
		}
	}
}
int suaPhanTuTheoMa(List &l, char id[]) {
		Node *q = timXoa(l, id);
		if(q==NULL) {
			printf("Khong tim thay\n");
			return 0;
		}
		//Neu tim thay
		nhapPhong(l, q->data);
		return 1;
}
int xoaPhanTuTheoMa(List &l, char id[]) {
	if(strcmp(l.First->data.id, id) == 0) {
		removeFirst(l);
		return 1;
	} else {
		Node *q = timXoa(l, id);
		if(q==NULL) {
			printf("Khong tim thay\n");
			return 0;
		}
		removeAfter(l, q);
		return 1;
	}
}

void removeFirst(List &l) {
	Node *p = l.First;
	l.First = p->link;
	if(p==l.Last) l.Last == NULL;
	delete p;
}

Node *timXoa(List l, char x[]) {
	Node *p = l.First;
	while(p != l.Last && strcmp(p->data.id, x) != 0) {
		p = p->link;
	}
	if(p != l.Last) return p;
	
	return NULL;
}

void removeAfter(List &l, Node *q) {
	Node *p = q->link;
	q->link = p->link;
	if(p==l.Last) l.Last = NULL;
	delete p;
}

void xuatThanhTienNhoNhat(List l) {
	long minThanhTien = l.First->data.thanhTien;
	Node *min = l.First;
	for(Node *p = l.First; p != l.Last; p = p->link) {
			if(p->data.thanhTien < minThanhTien) {
				min = p;
			}
	}
	int stt = 1;
	inTieuDe();
	xuatPhong(min->data, stt);
}
