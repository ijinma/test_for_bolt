#define NO_INLINE __attribute__((noinline))
typedef enum{
	false,
	true
} bool;

bool NO_INLINE BubbleSort(int a[], int len, bool sortBy)
{
	int i, j, temp;
	for (j = 0; j < len - 1; j++){
		for (i = 0; i < len - 1 - j; i++){
			bool sorted = sortBy ? (a[i] > a[i + 1]) : (a[i] < a[i + 1]);
			if (sorted){
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
			}
		}
	}
	return true;
}

int main()
{
	int loopCount = 2000000;

	int arr[] = {
		683, 507, 325, 750, 610, 214, 811, 364, 692, 879,
		436, 960, 571, 979, 154, 726, 115, 944, 984, 445,
		397, 173, 176, 884, 280, 525, 377, 543, 500, 271,
		186, 685, 652, 424, 806, 492, 574, 756, 741, 872,
		194, 819, 739, 635, 306, 179, 965, 299, 627, 278,
		439, 241, 191, 691, 801, 423, 430, 509, 930, 410,
		729, 379, 207, 779, 235, 102, 416, 931, 877, 763,
		725, 545, 513, 771, 254, 432, 579, 317, 850, 408,
		228, 900, 747, 339, 426, 923, 431, 946, 657, 660,
		987, 114, 532, 744, 721, 531, 883, 312, 839, 689};

	int len = sizeof(arr) / sizeof(arr[0]);

	while (loopCount--){
		bool sortBy = (loopCount % 2 == 0);
		bool res = BubbleSort(arr, len, sortBy);
		if(!res){
			break;
		}
	}

	return 0;
}
