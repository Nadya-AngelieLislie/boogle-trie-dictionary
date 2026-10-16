#include<stdio.h> // Dimasukkan untuk input output standard
#include<string.h> // Dimasukkan utamanya untuk pemakaian strcpy dan strlen
#include<stdlib.h> // Dimasukkan utamannya untuk memory allocation
#define START 26 // Didefine sebagai variabel konstan yang akan digunakan di sepanjang program

// Function untuk menampilkan fitur-fitur yang program ini sediakan
void Menu(){
	printf("Welcome to BOOGLE\n");
	printf("Chose from the following options:\n");
	printf("1. Release a new slang word\n");
	printf("2. Search a slang word\n");
	printf("3. View all slang words starting with a certain prefix word\n");
	printf("4. View all slang words\n");
	printf("5. Exit\n");
	printf(">> ");
}

// Variabel Global yang dapat dipanggil baik di dalam ataupun di luar function main
char slangword[100];
char description[100];
char searchslang[30];

// Struct (gabungan beberapa variabel yang beda jenisnya) untuk menyimpan data dari setiap node trie
struct Node{
	Node *children[START];
	char desc[100];
	int END;
};

// Function untuk membuat node baru
Node *createNode(){
	// Alokasi memori untuk menjadi tempat penyimpanan data node
	Node *temp = (Node*)malloc(sizeof(Node));
	
	// Periksa apakah alokasi memori berhasil
	// Bila gagal (misalnya karena memori di laptop penuh), temp akan sama dengan NULL
	if(temp == NULL){
		return NULL;
	}
	
	// Loop untuk menginisialisasikan bahwa ke-26 anak yang dimiliki tiap node mula-mula adalah NULL
	for(int i = 0; i<START; i++){
		temp->children[i] = NULL;
	}
	
	// Menginisialisasikan bahwa mula-mula, tiap node bukanlan pengakhir kata
	temp->END = 0;
	// Mengembalikan node yang telah berhasil dibuat
	return temp;
}

// Membuat node root yang paling pertama dan menjadi parent dari semua childrennya
Node *root = createNode();

// Function untuk menangani inputan dalam huruf kapital
// Agar tidak terjadi error bila ada yang menggunakan huruf kapital dan agar program dapat dengan seragam menggunakan huruf kecil
void capitalizationHandling(char slang[]){
	// Menghitung jumlah karakter dari sebuah kata
	int length = strlen(slang);
	
	// Loop untuk mencari huruf kapital
	// Bila ada, diubah menjadi huruf kecil menggunakan konsep ASCII
	for(int i = 0; i<length; i++){
		if(slang[i]<'a' || slang[i]>'z'){
			slang[i]+=32;
		}
	}
}

// Function untuk memasukkan node baru ke dalam trie
Node *push (Node *root, char word[], char description[]){
	// Memastikan bahwa inisialisasi root berhasil
	if (root == NULL){
		root = createNode();
	}
	// Membuat node curr yang menunjuk pada root
	Node *curr = root;
	// Menghitung jumlah karakter yang berada di dalam kata
	int length = strlen(word);
	
	// Loop untuk mencari apakah huruf yang ada di dalam kata yang ingin kita input sudah ada?
	// Ditelusuri sampai buntu, tidak ada jalur yang sesuai dengan huruf berikutnya atau hingga kata sudah habis ditelusuri
	for(int i = 0; i<length; i++){
		int index = word[i] - 'a';
		if(curr->children[index] == NULL){
			curr->children[index] = createNode();
		}
		curr = curr->children[index];
	}
	
	// Memeriksa bila kata yang ingin dimasukkan sudah pernah ada atau merupakan kata yang baru
	if(curr->END){
		// Kasus kata yang sudah pernah ada
		printf("Successfully updated a slang word.\n");
	}else{
		// Kasus kata yang dimasukkan baru 
		printf("Successfully released a new slang word.\n");
	}
	
	// Menandai bahwa node terakhir adalah penanda kata telah berakhir
	curr->END = 1;
	// Memasukkan deskripsi kata ke dalam node kata
	strcpy(curr->desc, description);
	
	// Mengembalikan parent terutama
	return root;
}

// Function di bawah ini digunakan untuk mencari kata dari data trie
Node *search(Node *root, char target[]){
	// Membuat node curr yang menunjuk pada root
	Node *curr = root;
	// Menghitung jumlah karakter yang berada di dalam kata
	int length = strlen(target);
	
	// Memastikan bahwa inisialisasi root berhasil
	if(root == NULL){
		return NULL;
	}
	
	// Loop untuk menelurusi trie sesuai alfabet dari kata yang ingin dicari
	for(int i = 0; i<length; i++){
		int index = target[i]-'a';
		// Bila tidak ada alfabet lain yang sesuai, return NULL yang berarti, pencarian gagal
		if(curr->children[index] == NULL){
			return NULL;
		}
		curr = curr->children[index];
	}
	
	// Mengecek bila ujung dari node yang ditelusuri sudah sesuai dengan kata yang dicari dan penanda akhir katanya true
	if(curr->END == 1){
		printf("\n");
		// Node dengan kata yang berhasil ditemukan dikembalikan
		return curr;
	}
	else{
		// Kata gagal untuk ditemukan
		return NULL;
	}
}

// Variabel Global yang dapat dipanggil di luar maupun di dalam function main
char wordlist[300][300];
int count = 0;

// Function Rekursi untuk menampilkan semua kata yang terdapat di dalam trie
void Display(Node *root, char *pre, int length){
	// Memastikan bahwa inisialisasi root berhasil
	if(root == NULL){
		return;
	}
	
	// Syarat Rekursi berhenti, yautu saat node tersebut memiliki keterangan sebagai penghenti kata
	if(root->END == 1){
		// Menandakan akhir dari sebuah kata
		pre[length] = '\0';
		// Menyalin kata ke dalam array of strings
		strcpy(wordlist[count], pre);
		// Jumlah kata yang ditemukan bertambah 1
		count++;
	}
	
	// Loop untuk menelusuri semua jalur yang mungkin untuk dilalui sekaligus memanggil rekursi secara berulang
	for(int i = 0; i<START; i++){
		// Kondisi bila belum mencapai ujung dari trie
		if(root->children != NULL){
			// Kata diupdate misalnya dari hal ditambah o menjadi halo
			pre[length] = i+'a';
			// Rekursi, memanggil ulang fungsi ini sampai syarat berhenti (yang if root->END == 1) tercapai
			Display(root->children[i], pre, length+1);
		}
	}
}

// Variabel Global yang dapat dipanggil di luar maupun di dalam main
int counts = 0;

// Function untuk merekomendasikan kata dari dictionary berdasarkan awalan kata yang diberikan
void wordsRecc(Node *root, char prefix[]){
	// Membuat node curr yang menunjuk pada root
	Node *curr = root;
	// Menghitung jumlah karakter yang berada di dalam kata
	int length = strlen(prefix);
	
	// Memastikan bahwa inisialisasi curr berhasil
	if(curr == NULL){
		return;
	}
	// Syarat Rekursi berhenti, yautu saat node tersebut memiliki keterangan sebagai penghenti kata
	else if(curr->END == 1){
		// Jumlah kata dengan prefix yang sama ditambah 1 dan kata tersebut diprint
		counts++;
		printf("%d. %s\n", counts, prefix);
	}
	
	// Loop untuk menelusuri semua kemungkinan kata dengan prefix yang sama
	for(int i = 0; i<START; i++){
		// Kondisi saat node masih memiliki anak untuk dikunjungi
		if(curr->children[i] != NULL){
			char newPre[100];
			strcpy(newPre, prefix);
		
			length = strlen(newPre);
			// Mengupdate data prefix dengan menambah alfabet dari node yang beri dikunjungi
			newPre[length] = i+'a';
			newPre[length+1] = '\0';
			// Rekursi, memanggil ulang fungsi ini sampai syarat berhenti (yang if root->END == 1) tercapai
			wordsRecc(curr->children[i], newPre);
		}
	}
}

// Function untuk mencari kata dengan awalan tertentu
void byPrefix(Node *root, char prefix[]){
	// Membuat node curr yang menunjuk pada root
	Node *curr = root;
	// Menghitung jumlah karakter yang berada di dalam kata
	int length = strlen(prefix);
	
	// Loop untuk mencari keberadaan kata dengan prefix yang diinginkan
	for(int i = 0; i<length; i++){
		// Inisialisasi index
		int index = prefix[i]-'a';
		// Kondisi saat prefix tidak ditemukan dalam data trie
		if(curr->children[index] == NULL){
			printf("\nThere is no prefix \"%s\" int the dictionary.", prefix);
			return;
		}
		// Agar loop dapat menelusuri seluruh node yang memungkinkan
		curr = curr->children[index];
	}
	// Kondisi saat prefix ditemukan
	printf("\nWords starts with \"%s\":\n", prefix);
	// Memanggil function yang akan menprint kata-kata dengan prefix atau awalan yang sama
	wordsRecc(curr, prefix);
}

// Function untuk membebaskan memori yang baru saja digunakan oleh trie
void freeNode(Node *node){
	// Looping untuk membebaskan semua node dan anak-anaknya dengan rekursi
	for(int i = 0; i<START; i++){
		if(node->children[i] != NULL){
			freeNode(node->children[i]);
		}
		else{
			continue;
		}
	}
	// Data dan memori dibebaskan
	free(node);
}

// Function untuk memvalidasi kata yang dimasukkan saat insert data
void validateword(char word[]){
	// Menghitung jumlah karakter yang berada di dalam kata
	int len = strlen(word);
	// Inisialisasi variabel penanda
	int wrong = 0;
	// Looping untuk mencari keberadaan spasi dari inputan
	for(int i = 0; i<len; i++){
		if(word[i]==' '){
			wrong++;
		}
	}
	
	// Selama ada spasi atau kata hanya terdiri dari satu hurf, akan looping
	while(wrong>0 || len<=1){
		printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
		// Inputan data diambil
		scanf("%[^\n]", word); 
		// Mengambil enter setelah imputan agar tidak menggangu sistem
		getchar();
		
		// Menghitung jumlah karakter yang berada di dalam kata baru
		len = strlen(word);
		// Set ulang variabel penanda menjadi kondisi awal sebelum dipakai lagi
		wrong = 0;
		// Looping untuk mencari keberadaan spasi dari inputan
		for(int i = 0; i<len; i++){
			if(word[i]==' '){
				wrong++;
			}
		}
	}
	// Memanggil Function untuk mengatasi keberagaman huruf (huruf besar dan kecil) agar menjadi seragam, yaitu semua huruf kecil
	capitalizationHandling(word);
}

// Function untuk memvalidasi kata yang dimasukkan saat search data
void validatesearch(char word[]){
	// Menghitung jumlah karakter yang berada di dalam kata
	int len = strlen(word);
	// Inisialisasi variabel penanda
	int wrong = 0;
	// Looping untuk mencari keberadaan spasi dari inputan
	for(int i = 0; i<len; i++){
		if(word[i]==' '){
			wrong++;
		}
	}
	
	// Selama ada spasi atau kata hanya terdiri dari satu hurf, akan looping
	while(wrong>0 || len<=1){
		printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
		// Inputan data diambil
		scanf("%[^\n]", word);
		// Mengambil enter setelah imputan agar tidak menggangu sistem
		getchar();
			
		// Menghitung jumlah karakter yang berada di dalam kata baru	
		len = strlen(word);
		// Set ulang variabel penanda menjadi kondisi awal sebelum dipakai lagi
		wrong = 0;
		// Looping untuk mencari keberadaan spasi dari inputan
		for(int i = 0; i<len; i++){
			if(word[i]==' '){
				wrong++;
			}
		}
	}
	// Memanggil Function untuk mengatasi keberagaman huruf (huruf besar dan kecil) agar menjadi seragam, yaitu semua huruf kecil
	capitalizationHandling(word);
}

// Function untuk memvalidasi kalimat yang dimasukkan sebagai definisi
void validatedesc(char desc[]){
	// Menghitung jumlah karakter yang berada di dalam deskripsi kata
	int len2 = strlen(description);
	
	// Inisialisasi variabel-variabel penanda
	int right = 0;
	int valid = 0;
	// Looping untuk menghitung jumlah spasi dari inputan
	for(int i = 0; i<len2; i++){
		// Kondisi saat spasi tidak berlokasi di ujung ataupun awal kalimat
		if(description[i]==' ' && i!=len2-1 && i!=0){
			right++;
			// Kondisi saat inputan adalah spasi beruntun
			if(description[i-1]==' ' || description[i+1]==' '){
				valid++;
			}
		}
	}
	
	// Bila spasi lebih besar atau sama dengan dua dan itu bukanlah hasik dari spasi beruntun, loop akan berhenti
	while(right<2 || valid>0){
		printf("Input a new slang word description [Must be more than 2 words]: ");
		// Inputan data diambil
		scanf("%[^\n]", description); 
		// Mengambil enter setelah imputan agar tidak menggangu sistem
		getchar();
			
		// Menghitung jumlah karakter yang berada di dalam deskripsi kata baru
		len2 = strlen(description);
		// Set ulang variabel penanda menjadi kondisi awal sebelum dipakai lagi
		right = 0;
		valid = 0;
		// Looping untuk menghitung jumlah spasi dari inputan
		for(int i = 0; i<len2; i++){
			// Kondisi saat spasi tidak berlokasi di ujung ataupun awal kalimat
			if(description[i]==' ' && i!=len2-1 && i!=0){
				right++;
				// Kondisi saat inputan adalah spasi beruntun
				if(description[i-1]==' ' || description[i+1]==' '){
					valid++;
				}
			}
		}
	}
}

// Function utama yang akan dieksekusi paling pertama kali oleh program
int main(){
	// Define variabel untuk menyimpan pilihan menu dalam integer
	int pilihan;
	
	// Membersihkan layar sebelum melanjutkan perjalanan program
	system("cls");
	// Memanggil Function untuk menampilkan fitur-itur yang program ini sediakan
	Menu();
	// Mengambil data pemilihan menu dan "enter" (menggunakan getchar)
	scanf("%d", &pilihan); getchar();	

	// Validasi pilihan harus berada di menu
	while(pilihan<1 || pilihan>5){
		printf("Must be a number in between 1-5!\n");
		printf(">> ");
		scanf("%d", &pilihan); getchar();
	}
	
	// Switch case untuk memecah langkah yang akan dilaksanakan sesuai dengan menu yang dipilih
	switch(pilihan){
		// Kasus pemilihan menu insert slag words and definition
		case 1:{
			// Membersihkan layar sebelum melanjutkan perjalanan program
			system("cls");
			
			// Meminta inputan slang word
			printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
			// Mengambil inputan
			scanf("%[^\n]", slangword); 
			// Mengambil enter
			getchar();
			// Memanggil Function untuk memvalidasi kesesuaian inputan
			validateword(slangword);
			
			// Meminta inputan deskripsi kata
			printf("Input a new slang word description [Must be more than 2 words]: ");
			// Mengambil inputan
			scanf("%[^\n]", description); 
			// Mengambil enter	
			getchar();
			// Memanggil Function untuk memvalidasi kesesuaian inputan
			validatedesc(description);
			
			// Memasukkan data ke trie dengan memanggil Function push
			root = push(root, slangword, description);
			
			printf("\n");
			printf("Press enter to continue...");
			// Mengambil enter	
			getchar();
			// Memanggil kembali Function utama
			main();
			break;
		}
		case 2:{
			// Membersihkan layar sebelum melanjutkan perjalanan program
			system("cls");
			
			// Meminta inputan slang word yang ingin dicari
			printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
			// Mengambil inputan
			scanf("%[^\n]", searchslang);
			// Mengambil enter
			getchar();
			// Memanggil function untuk menvalidasi inputan kata
			validatesearch(searchslang);
			
			Node *temp = NULL;
			// Memanggil function search
			temp = search(root, searchslang);
			
			// If case kalau return dari search functionnya NULL atau tidak
			if(temp == NULL){
				printf("\nThere is no word \"%s\" in the dictionary.\n", searchslang);
			}
			else{
				printf("Slang word : %s\n", searchslang);
				printf("Description : %s\n\n", temp->desc);
			}
			
			printf("Press enter to continue...");
			// Mengambil enter	
			getchar();
			// Memanggil kembali Function utama
			main();
			break;
		}
		case 3:{
			// Membersihkan layar sebelum melanjutkan perjalanan program
			system("cls");
			char searchpre[30];
			
			printf("Input a prefix to be searched: ");
			scanf("%[^\n]", searchpre); getchar();
			
			// Memastikan jumlah kata dengan prefix yang sama dimulai dari nol
			counts = 0;
			// Memanggil function untuk menemukan kata dengan prefix yang sama dengan inputan
			byPrefix(root, searchpre);
			
			printf("\n");
			printf("Press enter to continue...");
			// Mengambil enter	
			getchar();
			// Memanggil kembali Function utama
			main();
			break;
		}
		case 4:{
			// Membersihkan layar sebelum melanjutkan perjalanan program
			system("cls");
			// Define array of characters
			char pre[30];
			// Inisialisasi variabel penanda jumlah kata yang berada di trie
			count = 0;
			// Memanggil Function untuk menampilkan semua kata yang terdapat di dalam tree berdasarkan urutan abjad
			Display(root, pre, 0);
			
			// Mengecek kondisi saat jumlah kata di dalam tree tidak kurang dari nol = trienya ada data
			if(count>0){
				printf("List of all slang words in the dictionary:\n");
				// Looping untuk memprint keluar semua kata dalam trie
				for(int i = 0; i<count; i++){
					printf("%d. %s\n", i+1, wordlist[i]);
				}	
				printf("\n");
			}
			// Kondisi saat tidak ada kata di dalam trie
			else{
				printf("There is no slang word yet in the dictionary.\n");
			}
			
			printf("Press enter to continue...");
			// Mengambil enter	
			getchar();
			// Memanggil kembali Function utama
			main();
			break;
		}
		case 5:{
			// Membersihkan layar sebelum melanjutkan perjalanan program
			system("cls");
			// Membebaskan semua data dan memori yang telah digunakan
			freeNode(root);
			printf("Thank you... Have a nice day :)\n");
			break;
		}
	}
	// mengembalikan 0 sebagai penanda program berjalan sesuai dengan rencana
	return 0;
}
