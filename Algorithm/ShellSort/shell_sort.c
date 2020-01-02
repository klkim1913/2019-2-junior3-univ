#include <stdio.h>

void ShellSort(int list[], int size);
void InsertionSort(int list[], int start, int end, int gap);
void PrintList(int list[], int size, int gap);

int main() {

	int arr1[11] = { 23,1,6,37,101,78,19,8,93,255,157 };
	int arr2[14] = { 54,12,76,435,21,96,81,221,154,762,326,72,11,55 };
	int size;

	size = sizeof(arr1) / sizeof(int);
	printf("입력배열: ");
	PrintList(arr1, size, size + 1);
	ShellSort(arr1, size);	// 배열과 요소 개수 전달

	return 0;
}

void InsertionSort(int list[], int start, int end, int gap)	// start는 부분리스트 시작인덱스, end는 전체리스트 마지막 인덱스, gap은 간격
{
	int i, j, key;

	for (i = start + gap; i <= end; i += gap) // 두번째 요소부터 마지막 요소까지 간격만큼 이동
	{
		key = list[i];	// 삽입할 요소를 키에 저장
		for (j = i - gap; j >= start && list[j] > key; j-=gap) // 부분리스트 바로앞부터 비교해나가면서 처음으로 가거나 키값보다 작은 값이 나오면 멈춤
		{
			list[j + gap] = list[j];	// 오른쪽으로 한칸씩 밀어넣기
		}
		list[j + gap] = key;	// 현재 j는 key보다 작으므로 한간격 앞에 키값을 넣음
	}
}
void ShellSort(int list[], int size) {

	int i, gap;

	for (gap = size / 2; gap >= 1; gap /= 2) // 간격은 크기의 반씩 줄여나간다.
	{
		if (gap % 2 == 0) gap++;	// 짝수일경우 중복이 많아지므로 홀수로 잡는다.
		printf("간격 %d 정렬 전: ", gap);
		PrintList(list, size, gap);
		for (i = 0; i < gap; i++)	// 시작인덱스를 기점으로 부분리스트를 하나씩 정렬
		{
			InsertionSort(list, i, size - 1, gap);	// 삽입정렬
		}
		printf("간격 %d 정렬 후: ", gap);
		PrintList(list, size, gap);
	}
}

void PrintList(int list[], int size, int gap) {

	int i;

	for (i = 0; i < size; i++) {
		printf("%d ", list[i]);
		if ((i + 1) % gap == 0) printf("/ ");
	}
	printf("\n\n");
}