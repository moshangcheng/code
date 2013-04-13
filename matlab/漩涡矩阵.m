M = input('Please input M:');
N = input('Please input N:');
a = zeros(M, N);
if M > N
    min = N;
else
    min = M;
end
i = 0;
currentValue = 1;
while 2*i < min 
    positionX = i+1;
    positionY = i+1;
    j = 0;
    while j+2*i < N
        a(positionX, positionY) = currentValue;
        currentValue = currentValue + 1;
        positionY = positionY+1;
        j = j+1;
    end
    if currentValue > M*N
        break;
    end
    
    
    positionX = positionX+1;
    positionY = positionY-1;
    j = 1;
    while j+2*i < M
        a(positionX, positionY) = currentValue;
        currentValue = currentValue + 1;
        positionX = positionX+1;
        j = j+1;
    end
    if currentValue > M*N
        break;
    end
    
    positionX = positionX-1;
    positionY = positionY-1;
    j = 1;
    while j+2*i < N
        a(positionX, positionY) = currentValue;
        currentValue = currentValue + 1;
        positionY = positionY-1;
        j = j+1;
    end
    
    positionX = positionX-1;
    positionY = positionY+1;
    j = 1;
    while j+2*i < M-1
        a(positionX, positionY) = currentValue;
        currentValue = currentValue + 1;
        positionX = positionX-1;
        j = j+1;
    end
    
    i = i+1;
end
disp(a)

