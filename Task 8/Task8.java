import java.util.Random;


public class Task8 {
   public static void main(String [] args) {


       //normal wieght of a metal piece so a fake one will have weight of 1 (one kg less)
       int NormalWeight = 2;


       //creating array of boxes and initialising all with right weights
       int[] box = new int[50];
       for (int i = 0; i < 50; i++) {
           box[i] = 50 * NormalWeight;
       }


       //selecting a random box to have fake pieces of metal
       Random rand = new Random();
       int randomNumber = rand.nextInt(50);


       //now we have a random box that have fake metal pieces
       box[randomNumber] = 50 * (NormalWeight - 1);
       System.out.println("The random fake box index = " + randomNumber);


       int sumWeWant = 0;
       int sum =0;


       //we take 1 piece from box 1 & 2 pieces from box 2 & 3 pieces from box 3 etc...
       //if there were no fake pieces sum would be equal to sumWeWant
       for(int i=0;i<50;i++){
           sum += (box[i] /50)*(i+1) ;
           sumWeWant += (50*NormalWeight /50)*(i+1) ;
       }

       System.out.println("The calculated sum = "+ sum);
       System.out.println("If there is no fake metal the sum would be = "+ sumWeWant);


       //we use digital scale to know the sum and remove it from sum we want
       int rest = sumWeWant-sum -1;


       System.out.println("Difference between the two gives us the index of the fake metal box --> " + rest);


   }
}
