import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        int[] arr1 = {1,2,3,4,5};
        int [] arr2 = {2,3,4,4,5};

        ArrayList<Integer> list = new ArrayList<>();
        int i=0;
        int j=0;
        
        while(i<arr1.length && j < arr2.length) {
            if(arr1[i] <= arr2[j] && arr1[i] != list.get(list.size()-1)) {
                list.add(arr1[i]);
                i++;
            }else if(arr1[i] > arr2[j] && arr2[j] != list.get(list.size()-1)) {
                list.add(arr2[j]);
                j++;
            }
        }
        while(i<arr1.length) {
            if(arr1[i] != list.get(list.size()-1)) {
                list.add(arr1[i]);
            }
            i++;
        }

        while(j<arr2.length) {
            if(arr2[i] != list.get(list.size()-1)) {
                list.add(arr1[i]);
            }
            j++;
        }
        
    }
}
