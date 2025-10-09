


c = [-50,-40,-30,-20,-10,0,10,20,30,40,50];      
    f = 1:10:size(c);
    k = 1:10:size(c);
    i=0;
    while(i<size(c))

   
    f(i) = (9/5)*c(i)+32;
    k(i) = c(i) + 273.15;
    i = i+1;
    disp(c(i));
    disp(f(i));
    disp(k(i));

    end
   


   