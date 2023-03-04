#include <iostream>
#include <time.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

void replace(float**& newarr, float ValToBeChgd, float NewValue, int rows, int cols);
int FindFirst(float**& newarr, int j, int rows);
int FindLast(float**& newarr, int j, int rows);

//EXCEPTION AT LINE 287 SOMETIMES FIX ISSUE



class node {
public:
	int row;
	int col_start;
	int col_end;
	node* next;
	node() {
		row = 0;
		col_start = 0;
		col_end = 0;
		next = NULL;
	}
};

class List {
public:
	node* head;
	List() {
		head = NULL;
	}
	void addNode(int r, int col_s, int col_e) {
		if (!head)
		{
			head = new node();
			head->row = r;
			head->col_start = col_s;
			head->col_end = col_e;
		}
		else {
			node* holder = new node();
			holder->row = r;
			holder->col_start = col_s;
			holder->col_end = col_e;
			node* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = holder;
		}
	}
	void Print() {
		node* temp = head;
		int r = 0;
		while (temp->next != NULL)
		{
			if (temp->col_start != -1)
			{
				r = temp->row;
				cout << temp->col_start << "  " << temp->col_end << "  ";
				if (temp->next != NULL)
				{
					temp = temp->next;
				}
				if (temp->row != r)
				{
					cout << "-1" << endl;
				}
			}
			else {
				cout << "-1" << endl;
				temp = temp->next;
			}
		}
	}
};




int main()
{
	int choice;
	while (true)
	{


		cout << "Which Q(1,2,4): ";
		cin >> choice;
		if (choice == 1)
		{


			// Mat dst;
			Mat img = imread("C:/Users/muham/Downloads/SegmentedOutputs/mIMD427.bmp", IMREAD_GRAYSCALE);
			img.convertTo(img, CV_32F);
			Mat cmp = imread("C:/Users/muham/Downloads/GroundTruths/IMD427_lesion.bmp", IMREAD_GRAYSCALE);
			cmp.convertTo(cmp, CV_32F);
			float label = 1;
			int count = 0;
			imshow("First OpenCV Application", img);





			float** newarr = new float* [img.rows];
			for (int i = 0; i < img.rows; i++)
			{
				newarr[i] = new float[img.cols];
			}

			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols; j++)
				{
					newarr[i][j] = -1.0;
				}

			}



			float** arr = new float* [img.rows];
			for (int i = 0; i < img.rows; i++)
			{
				arr[i] = new float[img.cols];
			}


			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols; j++)
				{

					arr[i][j] = img.at<float>(i, j);

				}
			}

			label = 1;
			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols;j++)
				{
					if (arr[i][j] == 255.0)
					{
						//right
						if (j == 0 && i > 0)
						{
							if (arr[i - 1][j] == 0.0 && arr[i - 1][j + 1] == 0.0)
							{
								newarr[i][j] = label;
								label++;
							}
							else if (newarr[i - 1][j] != 0.0 && newarr[i - 1][j + 1] != 0.0)
							{
								if (newarr[i - 1][j] < newarr[i - 1][j + 1])
								{
									newarr[i][j] = newarr[i - 1][j];
									newarr[i - 1][j + 1] = newarr[i][j];
								}
								else
								{
									newarr[i][j] = newarr[i - 1][j + 1];
									newarr[i - 1][j] = newarr[i][j];
								}


							}


							else if (newarr[i - 1][j] != 0.0)
							{
								newarr[i][j] = newarr[i - 1][j];
							}
							else if (newarr[i - 1][j + 1] != 0.0)
							{
								newarr[i][j] = newarr[i - 1][j + 1];
							}

						}
						//left
						else if (j == img.cols && i > 0)    //MIGHT HAVE TO ADD A -1
						{
							if (newarr[i - 1][j] == 0.0 && newarr[i - 1][j - 1] == 0.0 && newarr[i][j - 1] == 0.0)
							{
								newarr[i][j] = label;
							}
							else if (newarr[i - 1][j] != 0.0 && newarr[i - 1][j - 1] != 0.0 && newarr[i][j - 1] != 0.0)////
							{
								if (newarr[i - 1][j] < newarr[i - 1][j - 1] && newarr[i - 1][j] < newarr[i][j - 1])
								{
									newarr[i][j] = newarr[i - 1][j];
									newarr[i - 1][j - 1] = newarr[i][j];
									newarr[i][j - 1] = newarr[i][j];
								}
								else if (newarr[i - 1][j - 1] < newarr[i - 1][j] && newarr[i - 1][j - 1] < newarr[i][j - 1])
								{
									newarr[i][j] = newarr[i - 1][j - 1];
									newarr[i - 1][j] = newarr[i][j];
									newarr[i][j - 1] = newarr[i][j];

								}
								else if (newarr[i][j - 1] < newarr[i - 1][j] && newarr[i][j - 1] < newarr[i - 1][j - 1])
								{
									newarr[i][j] = newarr[i][j - 1];
									newarr[i - 1][j] = newarr[i][j];
									newarr[i - 1][j - 1] = newarr[i][j];
								}
							}
							else if (newarr[i - 1][j] != 0.0)
							{
								newarr[i][j] = newarr[i - 1][j];
							}
							else if (newarr[i - 1][j - 1] != 0.0)
							{
								newarr[i][j] = newarr[i - 1][j - 1];
							}
							else if (newarr[i][j - 1] != 0.0)
							{
								newarr[i][j] = newarr[i][j - 1];
							}

						}
						//top
						else if (i == 0)
						{
							if (newarr[i][j - 1] == 0.0)
							{
								newarr[i][j] = label;
								label++;
							}
						}
						//center
						else
						{
							if (newarr[i][j - 1] == 0.0 && newarr[i - 1][j - 1] == 0.0 && newarr[i - 1][j] == 0.0 && newarr[i - 1][j + 1] == 0.0)
							{
								newarr[i][j] = label;
								label++;
							}
							else if (newarr[i][j - 1] != 0.0)
							{
								newarr[i][j] = newarr[i][j - 1];
							}
							else if (newarr[i - 1][j - 1] != 0.0)
							{
								newarr[i][j] = newarr[i - 1][j - 1];
							}
							else if (newarr[i - 1][j] != 0.0)
							{
								newarr[i][j] = newarr[i - 1][j];
							}
							else if (newarr[i - 1][j + 1] != 0.0)
							{
								newarr[i][j] = newarr[i - 1][j + 1];
							}



						}

					}
					else
					{
						newarr[i][j] = 0.0;
					}



				}
			}
			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols;j++)
				{
					if (newarr[i][j] != 0.0)
					{

						if (newarr[i][j] != newarr[i][j - 1])
						{

							replace(newarr, newarr[i][j - 1], newarr[i][j], img.rows, img.cols);
						}
						if (newarr[i][j] != newarr[i - 1][j - 1])
						{
							replace(newarr, newarr[i - 1][j - 1], newarr[i][j], img.rows, img.cols);

						}
						if (newarr[i][j] != newarr[i - 1][j])
						{
							replace(newarr, newarr[i - 1][j], newarr[i][j], img.rows, img.cols);

						}
						if (newarr[i][j] != newarr[i - 1][j + 1])
						{
							replace(newarr, newarr[i - 1][j + 1], newarr[i][j], img.rows, img.cols);

						}



					}

				}
			}

			int* Labels = new int[img.rows * img.cols];
			int* CountLabels = new int[img.rows * img.cols];

			for (int i = 0; i < img.rows * img.cols;i++)
			{
				Labels[i] = 0;
				CountLabels[i] = 0;
			}

			int num = 0;
			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols;j++)
				{
					if (newarr[i][j] != 0)
					{
						int x = 0;
						bool check = false;
						while (Labels[x] != 0)
						{
							if (Labels[x] == newarr[i][j])
							{
								check = true;
							}
							x++;
						}

						if (check == false)
						{
							Labels[num] = newarr[i][j];
							num++;
						}



					}
				}
			}

			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols;j++)
				{
					if (newarr[i][j] != 0)
					{
						int x = 0;
						while (Labels[x] != 0)
						{
							if (Labels[x] == newarr[i][j])
							{
								CountLabels[x]++;
							}
							x++;
						}
					}
				}
			}



			int max = CountLabels[0];
			int maxIndex = 0;
			for (int i = 0; i < img.rows * img.cols; i++)
			{
				if (CountLabels[i] > max)
				{
					max = CountLabels[i];
					maxIndex = i;
				}
			}



			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols;j++)
				{
					if (newarr[i][j] != Labels[maxIndex])
					{
						newarr[i][j] = 0;
					}
					else
					{
						newarr[i][j] = 255;
					}
				}
			}


			for (int j = 0; j < img.cols; j++)
			{
				int first = FindFirst(newarr, j, img.rows);
				int last = FindLast(newarr, j, img.rows);
				for (int i = 0; i < img.rows;i++)
				{
					if (i > first && i < last)
					{
						newarr[i][j] = 255;

					}
				}
			}



			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols;j++)
				{
					img.at<float>(i, j) = newarr[i][j];

				}
			}










			float TP = 0.0;
			float FP = 0.0;
			float FN = 0.0;

			float DC;

			float** cmparr = new float* [cmp.rows];
			for (int i = 0; i < cmp.rows; i++)
			{
				cmparr[i] = new float[cmp.cols];
			}


			for (int i = 0; i < cmp.rows; i++)
			{
				for (int j = 0; j < cmp.cols; j++)
				{

					cmparr[i][j] = cmp.at<float>(i, j);

				}
			}


			for (int i = 0; i < img.rows;i++)
			{
				for (int j = 0; j < img.cols; j++)
				{
					if (newarr[i][j] == 255.0 && cmparr[i][j] == 255.0)
					{
						TP++;
					}
					else if (newarr[i][j] == 0.0 && cmparr[i][j] == 255.0)
					{
						FP++;
					}
					else if (newarr[i][j] == 255.0 && cmparr[i][j] == 0.0)
					{
						FN++;
					}
				}
			}

			DC = (2 * TP) / (FN + (2 * TP) + FP);

			cout << TP << endl;
			cout << FP << endl;
			cout << FN << endl;
			cout << "dice coefficient = " << DC << endl;

			for (int i = 0; i < img.rows; i++)
			{
				delete[] arr[i];
				delete[] newarr[i];

			}
			delete[] arr;
			delete[] newarr;
			delete[] Labels;
			delete[] CountLabels;

			imshow("CONVERTED", img);

			imshow("GROUND TRUTH", cmp);

			waitKey(0);
			destroyAllWindows();









			waitKey(0);
			destroyAllWindows();


		}
		if (choice == 2)
		{
			Mat org = imread("C:/Users/muham/Downloads/OriginalImages/IMD427.bmp");
			imshow("ORIGINAL IMAGE", org);
			Mat img = imread("C:/Users/muham/Downloads/OriginalImages/IMD427.bmp", IMREAD_GRAYSCALE);
			img.convertTo(img, CV_32F);

			srand(time(0));

			float c1 = (rand() % 255) + 128;
			float c2 = (rand() % 127);

			float** arr1 = new float* [img.rows];
			for (int i = 0; i < img.rows; i++)
			{
				arr1[i] = new float[img.cols];
			}
			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols; j++)
				{
					arr1[i][j] = img.at<float>(i, j);
				}
			}

			int sum1 = 0;
			int sum2 = 0;
			int count1 = 0;
			int count2 = 0;

			for (int i = 0; i < img.rows;i++)
			{
				for (int j = 0; j < img.cols;j++)
				{
					if (abs(arr1[i][j] - c1) < abs(arr1[i][j] - c2))
					{
						sum1 = sum1 + arr1[i][j];
						count1++;

						if (sum1 / count1 != c1)
						{
							c1 = round(sum1 / count1);
						}

					}
					else
					{
						sum2 = sum2 + arr1[i][j];
						count2++;

						if (sum2 / count2 != c2)
						{
							c2 = round(sum2 / count2);
						}
					}

				}


			}


			cout << c1 << " " << c2 << endl;
			for (int i = 0; i < img.rows;i++)
			{
				for (int j = 0; j < img.cols;j++)
				{
					if (abs(arr1[i][j] - c1) < abs(arr1[i][j] - c2))
					{
						arr1[i][j] = 0;
					}
					else
					{
						arr1[i][j] = 255;
					}

				}
			}





			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols; j++)
				{
					img.at<float>(i, j) = arr1[i][j];
				}
			}




			Mat cmp = imread("C:/Users/muham/Downloads/SegmentedOutputs/mIMD427.bmp", IMREAD_GRAYSCALE);
			cmp.convertTo(cmp, CV_32F);


			float TP = 0.0;
			float FP = 0.0;
			float FN = 0.0;

			float DC = 0;

			float** cmparr = new float* [cmp.rows];
			for (int i = 0; i < cmp.rows; i++)
			{
				cmparr[i] = new float[cmp.cols];
			}


			for (int i = 0; i < cmp.rows; i++)
			{
				for (int j = 0; j < cmp.cols; j++)
				{

					cmparr[i][j] = cmp.at<float>(i, j);

				}
			}


			for (int i = 0; i < img.rows;i++)
			{
				for (int j = 0; j < img.cols; j++)
				{
					if (arr1[i][j] == 255.0 && cmparr[i][j] == 255.0)
					{
						TP++;
					}
					else if (arr1[i][j] == 0.0 && cmparr[i][j] == 255.0)
					{
						FP++;
					}
					else if (arr1[i][j] == 255.0 && cmparr[i][j] == 0.0)
					{
						FN++;
					}
				}
			}

			DC = (2 * TP) / (FN + (2 * TP) + FP);

			cout << TP << endl;
			cout << FP << endl;
			cout << FN << endl;
			cout << "dice coefficient = " << DC << endl;



			for (int i = 0; i < img.rows; i++)
			{
				delete[] arr1[i];

			}
			delete[] arr1;





			imshow("GRAYSCALE", img);




			waitKey(0);
			destroyAllWindows();



		}
		if(choice == 4)
		{


			Mat image = cv::imread("C:/Users/muham/Downloads/GroundTruths/IMD427_lesion.bmp");
			int r = image.rows;
			int c = image.cols;
			float** arr = new float* [image.rows];
			for (int i = 0; i < image.rows; i++)
			{
				arr[i] = new float[image.cols];
			}
			int x, y, z;
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					x = image.at<Vec3b>(i, j)[0];
					y = image.at<Vec3b>(i, j)[1];
					z = image.at<Vec3b>(i, j)[2];
					int h = x + y + z;
					h = h / 3;
					arr[i][j] = h;
				}
			}

			List list;

			int temp = 0;
			bool ran = false;

			for (int i = 0; i < r; i++)
			{
				ran = false;
				for (int j = 0; j < c; j++)
				{
					temp = 0;
					if (arr[i][j] != 0)
					{
						temp = j;
						while (j < c && arr[i][j] != 0) {
							j++;
						}
						list.addNode(i, temp, j - 1);
						ran = true;
					}
				}
				if (ran == false)
				{
					list.addNode(i, -1, -1);
				}
			}

			list.Print();

			for (int i = 0; i < r; i++)
			{
				delete[] arr[i];
			}
			delete[] arr;




		}


	}
	return 0;
}


void replace(float**& newarr, float ValToBeChgd, float NewValue, int rows, int cols)
{
	if (ValToBeChgd != 0)
	{

		for (int i = 0; i < rows; i++)
		{
			int j = 0;
			for (; j < cols; j++)
			{
				if (newarr[i][j] == ValToBeChgd)
				{
					newarr[i][j] = NewValue;
				}
			}
			if (newarr[i][j] == -1)
			{
				break;
			}
		}

	}



}
int FindFirst(float**& newarr, int j, int rows)
{
	for (int i = 0; i < rows;i++)
	{
		if (newarr[i][j] == 255)
		{
			return i;
		}
	}


	return rows;

}
int FindLast(float**& newarr, int j, int rows)
{
	for (int i = rows - 1; i >= 0;i--)
	{
		if (newarr[i][j] == 255)
		{
			return i;
		}
	}




}
