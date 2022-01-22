tic
n=length(A);
B=zeros(n,1);
cc=zeros(1,n);

for q=1:n
    if q>1
        B(q-1,1)=0;
    end

    B(q,1)=1;
    C = B;

    for j=1:(n-1)
        C = [ C (A^j)*B ];
    end
    
    cc(1,q)=rank(C);

    if mod(q,10)==0
        fprintf("%i\n",q)
    end
end
toc