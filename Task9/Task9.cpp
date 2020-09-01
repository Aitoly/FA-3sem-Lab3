#pragma warning(disable:4996)

#include<stdio.h>
#include<iostream>
#include<ctype.h>
#include<math.h>
#include<time.h>

///////////////////////////////////////////////////////////
///////////			Adress
//////////////////////////////////////////////////////////
typedef struct
{
	char* city;
	char* street;
	int house;
	int falt;
	int index;
}Adress;

void Init_Adress(Adress* adress, const char* city, const char* street, int house, int falt, int index)
{
	if (!adress)
	{
		return;
	}
	adress->city = (char*)malloc(strlen(city) + 1);
	adress->street = (char*)malloc(strlen(street) + 1);
	strcpy(adress->city, city);
	strcpy(adress->street, street);
	adress->house = house;
	adress->falt = falt;
	adress->index = index;
}

void Print_Adress(const Adress* adress)
{
	if (!adress)
	{
		return;
	}
	printf("\tCity: %s\n\tStreet: %s\n\tHouse: %d\n\tFlat: %d\n\tIndex: %d\n", adress->city, adress->street,
		adress->house, adress->falt, adress->index);
}

void Delete__Adress(Adress* adress)
{
	free(adress->city);
	free(adress->street);
}

///////////////////////////////////////////////////////////
///////////			Mail
//////////////////////////////////////////////////////////
typedef struct
{
	Adress adress;
	int weight;
	int id;
} Mail;

void Init_Mail(Mail* mail, const Adress* adress, int weight, int id)
{
	if (!adress || !mail)
	{
		return;
	}
	Init_Adress(&(mail->adress), adress->city, adress->street, adress->house, adress->falt, adress->index);
	mail->weight = weight;
	mail->id = id;
}

void Print_Mail(const Mail* mail)
{
	if (!mail)
	{
		return;
	}
	printf("Mail[id::%d]\n", mail->id);
	Print_Adress(&(mail->adress));
	printf("\tWeight: %d\n", mail->weight);
}

int compare(const void* mail1, const void* mail2)   // функция сравнения элементов массива
{
	if (!mail1 || !mail2)
	{
		return 0;
	}
	return ((Mail*)mail1)->id - ((Mail*)mail2)->id;
}

void Delete__Mail(Mail* mail)
{
	Delete__Adress(&(mail->adress));
}

///////////////////////////////////////////////////////////
///////////			Post
//////////////////////////////////////////////////////////
typedef struct
{
	Adress adress;
	Mail* mails;
	int count_of_mail;
}Post;

void Init_Post(Post* post, const Adress* adress)
{
	if (!adress || !post)
	{
		return;
	}
	Init_Adress(&(post->adress), adress->city, adress->street, adress->house, adress->falt, adress->index);
	post->mails = NULL;
	post->count_of_mail = 0;
}

void Delete_Post(Post* post)
{
	for (int i = 0; i < post->count_of_mail; i++)
	{
		Delete__Mail(post->mails + i);
	}
	free(post->mails);
}

void Print_Mails(const Post* post)
{
	if (!post)
	{
		return;
	}

	printf("======Post======\n");
	printf("<>Adress of post\n");
	Print_Adress(&post->adress);
	printf("<>Mails of post\n");
	for (int i = 0; i < post->count_of_mail; i++)
	{
		if ((post->mails + i))
		{
			Print_Mail((post->mails + i));
		}
	}
	printf("======Post======\n");
}

void Add_Mail(Post* post, Mail* mail)
{
	if (!mail || !post)
	{
		return;
	}

	post->count_of_mail++;
	post->mails = (Mail*)realloc(post->mails, post->count_of_mail * sizeof(Mail));
	Mail* t = post->mails + post->count_of_mail - 1;
	*t = *mail;

	qsort(post->mails, post->count_of_mail, sizeof(Mail), compare);
}

void Remove_Mail(Post* post, Mail* mail)
{
	if (!mail || !post)
	{
		return;
	}

	Delete__Mail(mail);
	int move = 0;
	for (int i = 0; i < post->count_of_mail; i++)
	{
		if (move)
		{
			Mail* t_in = post->mails + i - 1;
			Mail* t_out = post->mails + i;
			*t_in = *t_out;
		}
		if (!move && (post->mails + i) == mail)
		{
			Mail* t = post->mails + i;
			t = NULL;
			move = 1;
		}
	}
	post->count_of_mail--;
	post->mails = (Mail*)realloc(post->mails, post->count_of_mail * sizeof(Mail));
}

void Find_Print_Mail(Post* post, int id)
{
	if (!post)
	{
		return;
	}

	for (int i = 0; i < post->count_of_mail; i++)
	{
		if ((post->mails + i)->id == id)
		{
			Print_Mail(post->mails + i);
		}
	}
}


///////////////////////////////////////////
int main()
{
	Adress adr1, adr2, adr3;
	Init_Adress(&adr1, "New York", "Wall Street", 1, 2, 177010);
	Init_Adress(&adr2, "Moscow", "Tverskaya", 2, 4, 165010);
	Init_Adress(&adr3, "Lytkarino", "Sportivnaya", 5, 6, 165552);

	Mail mail1, mail2, mail3;
	Init_Mail(&mail1, &adr1, 190, 1889);
	Init_Mail(&mail2, &adr3, 250, 2441);
	Init_Mail(&mail3, &adr3, 300, 1995);

	Post post;
	Init_Post(&post, &adr2);
	//////////

	Add_Mail(&post, &mail1);
	Add_Mail(&post, &mail2);
	Add_Mail(&post, &mail3);

	Print_Mails(&post);

	system("pause");
	system("cls");

	Find_Print_Mail(&post, 2441);

	system("pause");
	system("cls");

	Remove_Mail(&post, &mail2);

	Print_Mails(&post);

	//////////
	Delete_Post(&post);

	return 0;
}