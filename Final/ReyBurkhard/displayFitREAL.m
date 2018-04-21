clear all;

%initialisation des variables pour parametres graphe

%load des donnees x,y
run('courbes.m');
%nombre de courbes
A = who('C*','');
LINE_WIDTH = 1;
polDegree = 3;
MARKER_SHAPE = '*';
WAIT = 3;
POL_LINE_WIDTH = 2;
MARKER_SIZE = 2;
LINE_STYLE = '-';
GRAPH_NAME = 'scan2.png';
MATRIX_COLOR = [;[1,0,0];[0,0,1];[1,0,0];[0,0,0];[0,0,1];[0,0,0];[1,0,0]];
 
close all;
%figure;
hold on;
 
 
 %titre du graphe
title(GRAPH_NAME);
 
%vecteur de taille degree+1 car il ya la cst!
P=0*ones(1,polDegree+1);
%permet de ploter les n courbes
for m=0 :length(A)-1
    
    eval(['X = C' int2str(m) '(:,1);']);
    eval(['Y = C' int2str(m) '(:,2);']);
    plot(X,Y,strcat(MARKER_SHAPE, LINE_STYLE), LINE_WIDTH, MARKER_SIZE, 'color', MATRIX_COLOR(m+1,:));
    legend(strcat('Courbe ', int2str(m)));
    
    %polyfit des courbes
    
    P1= polyfit(X,Y,polDegree);
    P(m+1,:)=P1;
    plot(X,polyval(P1,X), strcat(MARKER_SHAPE, LINE_STYLE), POL_LINE_WIDTH, MARKER_SIZE, 'color', MATRIX_COLOR(m+1,:));
   
end;
 
%temps d'affichage du graphe
pause(WAIT);
 %creation du fichier pdf
print('-dpdf', strcat(GRAPH_NAME,'.pdf'));
%creation du fichier contenant les coefficient des polynomes
xlswrite('P',P);
hold off;
close all;
