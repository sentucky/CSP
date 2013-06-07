xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 187;
 0.19869;0.10123;-0.34607;,
 0.00006;0.10123;-0.34607;,
 0.00006;0.40501;-0.34607;,
 0.19869;0.40501;-0.34607;,
 0.20981;0.18119;-0.50186;,
 0.47850;0.18119;-0.50186;,
 0.47855;0.00487;-0.27204;,
 0.20981;0.00000;-0.27204;,
 0.20981;0.41443;-0.34607;,
 0.47855;0.40956;-0.34607;,
 0.47850;0.37456;-0.50186;,
 0.20981;0.37456;-0.50186;,
 0.47850;0.37456;-0.50186;,
 0.20981;0.37456;-0.50186;,
 -0.20991;0.37456;-0.50186;,
 -0.47855;0.37456;-0.50186;,
 -0.47852;0.40956;-0.34607;,
 -0.20991;0.41443;-0.34607;,
 -0.20991;0.00000;-0.27204;,
 -0.47852;0.00487;-0.27204;,
 -0.47855;0.18119;-0.50186;,
 -0.20991;0.18119;-0.50186;,
 -0.20991;0.37456;-0.50186;,
 -0.47855;0.37456;-0.50186;,
 0.19869;0.10123;-0.34607;,
 0.20981;0.18119;-0.50186;,
 0.20981;0.00000;-0.27204;,
 0.42748;0.34192;0.77148;,
 0.42748;0.20320;0.76715;,
 0.42752;0.05116;0.63256;,
 0.42752;0.36726;0.63256;,
 0.19869;0.40501;-0.34607;,
 0.20981;0.37456;-0.50186;,
 0.19869;0.40501;-0.34607;,
 0.42752;0.36721;-0.33218;,
 0.42752;0.05110;-0.33218;,
 0.42748;0.19397;-0.46106;,
 0.42748;0.34341;-0.46539;,
 -0.19858;0.40501;-0.34607;,
 -0.42750;0.36726;0.63256;,
 -0.42750;0.05116;0.63256;,
 -0.42752;0.20320;0.76717;,
 -0.42752;0.34192;0.77150;,
 -0.19858;0.10123;-0.34607;,
 -0.20991;0.00000;-0.27204;,
 -0.20991;0.18119;-0.50186;,
 -0.19858;0.40501;-0.34607;,
 -0.20991;0.37456;-0.50186;,
 -0.42752;0.34341;-0.46541;,
 -0.42752;0.19397;-0.46108;,
 -0.42750;0.05110;-0.33218;,
 -0.42750;0.36721;-0.33218;,
 -0.20991;0.18875;0.80230;,
 -0.47855;0.18875;0.80230;,
 -0.47852;0.00487;0.64652;,
 -0.20991;0.00000;0.64652;,
 0.20981;0.00000;0.64652;,
 0.20981;0.18875;0.80230;,
 0.19869;0.10123;0.64652;,
 0.20981;0.41443;0.64652;,
 0.47855;0.40956;0.64652;,
 0.19869;0.40428;0.69701;,
 0.00006;0.40501;-0.34607;,
 0.00006;0.40428;0.69701;,
 -0.20991;0.41443;0.64652;,
 -0.19858;0.40428;0.69701;,
 -0.47852;0.40956;0.64652;,
 -0.20991;0.00000;0.64652;,
 -0.47852;0.00487;0.64652;,
 -0.47852;0.00487;-0.27204;,
 -0.20991;0.00000;-0.27204;,
 0.47855;0.00487;-0.27204;,
 0.47855;0.00487;0.64652;,
 0.20981;0.00000;0.64652;,
 0.20981;0.00000;-0.27204;,
 0.47855;0.00487;0.64652;,
 0.47854;0.05116;0.63256;,
 0.47850;0.20320;0.76716;,
 0.47850;0.18875;0.80230;,
 0.47850;0.37456;0.80230;,
 0.47850;0.34192;0.77149;,
 0.47854;0.36726;0.63256;,
 0.47855;0.40956;0.64652;,
 0.47855;0.40956;-0.34607;,
 0.47854;0.36721;-0.33218;,
 0.47850;0.34341;-0.46540;,
 0.47850;0.37456;-0.50186;,
 0.47850;0.19397;-0.46107;,
 0.47850;0.18119;-0.50186;,
 0.47854;0.05110;-0.33218;,
 0.47855;0.00487;-0.27204;,
 -0.47852;0.40956;0.64652;,
 -0.47852;0.36726;0.63256;,
 -0.47854;0.34192;0.77149;,
 -0.47855;0.37456;0.80230;,
 -0.47854;0.20320;0.76716;,
 -0.47855;0.18875;0.80230;,
 -0.47852;0.05116;0.63256;,
 -0.47852;0.00487;0.64652;,
 -0.47852;0.00487;-0.27204;,
 -0.47852;0.05110;-0.33218;,
 -0.47854;0.19397;-0.46107;,
 -0.47855;0.18119;-0.50186;,
 -0.47855;0.37456;-0.50186;,
 -0.47854;0.34341;-0.46540;,
 -0.47852;0.36721;-0.33218;,
 -0.47852;0.40956;-0.34607;,
 0.47854;0.05116;0.63256;,
 0.42752;0.05116;0.63256;,
 0.42748;0.20320;0.76715;,
 0.47850;0.20320;0.76716;,
 0.47850;0.34192;0.77149;,
 0.42748;0.34192;0.77148;,
 0.47850;0.34192;0.77149;,
 0.42748;0.34192;0.77148;,
 0.42752;0.36726;0.63256;,
 0.47854;0.36726;0.63256;,
 0.47854;0.36721;-0.33218;,
 0.42752;0.36721;-0.33218;,
 0.42748;0.34341;-0.46539;,
 0.47850;0.34341;-0.46540;,
 0.42748;0.34341;-0.46539;,
 0.42748;0.19397;-0.46106;,
 0.47850;0.19397;-0.46107;,
 0.47850;0.34341;-0.46540;,
 0.47850;0.19397;-0.46107;,
 0.42748;0.19397;-0.46106;,
 0.42752;0.05110;-0.33218;,
 0.47854;0.05110;-0.33218;,
 0.42752;0.05116;0.63256;,
 0.47854;0.05116;0.63256;,
 -0.47852;0.36726;0.63256;,
 -0.42750;0.36726;0.63256;,
 -0.42752;0.34192;0.77150;,
 -0.47854;0.34192;0.77149;,
 -0.42752;0.34192;0.77150;,
 -0.42752;0.20320;0.76717;,
 -0.47854;0.20320;0.76716;,
 -0.47854;0.34192;0.77149;,
 -0.42750;0.05116;0.63256;,
 -0.47852;0.05116;0.63256;,
 -0.47852;0.05110;-0.33218;,
 -0.42750;0.05110;-0.33218;,
 -0.42752;0.19397;-0.46108;,
 -0.47854;0.19397;-0.46107;,
 -0.47854;0.34341;-0.46540;,
 -0.47854;0.19397;-0.46107;,
 -0.42752;0.19397;-0.46108;,
 -0.42752;0.34341;-0.46541;,
 -0.47854;0.34341;-0.46540;,
 -0.42752;0.34341;-0.46541;,
 -0.42750;0.36721;-0.33218;,
 -0.47852;0.36721;-0.33218;,
 -0.42750;0.05116;0.63256;,
 -0.47852;0.05116;0.63256;,
 -0.19858;0.10123;-0.34607;,
 -0.19858;0.40501;-0.34607;,
 -0.47855;0.37456;0.80230;,
 -0.20991;0.37456;0.80230;,
 -0.19858;0.28265;0.76588;,
 -0.19858;0.40428;0.69701;,
 -0.20991;0.37456;0.80230;,
 -0.20991;0.37456;0.80230;,
 -0.47855;0.37456;0.80230;,
 -0.19858;0.10123;0.64652;,
 -0.20991;0.18875;0.80230;,
 -0.20991;0.00000;0.64652;,
 0.20981;0.37456;0.80230;,
 0.20981;0.18875;0.80230;,
 0.47850;0.18875;0.80230;,
 0.47850;0.37456;0.80230;,
 0.20981;0.37456;0.80230;,
 0.19869;0.40428;0.69701;,
 0.19869;0.28265;0.76588;,
 0.20981;0.37456;0.80230;,
 0.47850;0.37456;0.80230;,
 0.00006;0.40428;0.69701;,
 0.00006;0.28265;0.76588;,
 0.19869;0.28265;0.76588;,
 0.19869;0.40428;0.69701;,
 0.00006;0.10123;0.64652;,
 0.19869;0.10123;0.64652;,
 -0.19858;0.10123;0.64652;,
 -0.19858;0.28265;0.76588;,
 -0.19858;0.40428;0.69701;,
 0.20981;0.00000;0.64652;,
 0.47855;0.00487;0.64652;;
 
 78;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,5,4,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;22,21,20,23;,
 3;24,25,26;,
 4;27,28,29,30;,
 3;31,8,11;,
 4;32,25,24,33;,
 4;34,35,36,37;,
 3;38,14,17;,
 4;39,40,41,42;,
 3;43,44,45;,
 4;46,43,45,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 3;56,57,58;,
 4;59,60,9,8;,
 4;31,61,59,8;,
 4;62,63,61,31;,
 4;17,64,65,38;,
 4;16,66,64,17;,
 4;40,39,51,50;,
 4;67,68,69,70;,
 4;71,72,73,74;,
 4;30,29,35,34;,
 4;75,76,77,78;,
 4;79,78,77,80;,
 4;79,80,81,82;,
 4;83,84,85,86;,
 4;85,87,88,86;,
 4;88,87,89,90;,
 4;81,84,83,82;,
 4;89,76,75,90;,
 4;91,92,93,94;,
 4;93,95,96,94;,
 4;96,95,97,98;,
 4;99,100,101,102;,
 4;103,102,101,104;,
 4;103,104,105,106;,
 4;97,100,99,98;,
 4;105,92,91,106;,
 4;107,108,109,110;,
 4;111,110,109,112;,
 4;113,114,115,116;,
 4;117,118,119,120;,
 4;121,122,123,124;,
 4;125,126,127,128;,
 4;115,118,117,116;,
 4;129,130,128,127;,
 4;131,132,133,134;,
 4;135,136,137,138;,
 4;137,136,139,140;,
 4;141,142,143,144;,
 4;145,146,147,148;,
 4;149,150,151,152;,
 4;153,142,141,154;,
 4;151,132,131,152;,
 4;38,65,63,62;,
 4;2,1,155,156;,
 4;157,53,52,158;,
 3;159,160,161;,
 3;64,162,65;,
 4;66,163,162,64;,
 3;164,165,166;,
 4;159,161,165,164;,
 4;167,168,169,170;,
 3;171,172,173;,
 4;174,175,60,59;,
 3;61,174,59;,
 4;176,177,178,179;,
 4;177,180,181,178;,
 4;182,180,177,183;,
 4;183,177,176,184;,
 4;173,58,57,171;,
 4;168,185,186,169;;
 
 MeshMaterialList {
  1;
  78;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  96;
  0.000000;0.000000;-1.000000;,
  -0.983229;-0.072725;0.167247;,
  -0.124967;0.936724;0.327004;,
  0.669505;0.738718;-0.077835;,
  0.123849;0.937067;0.326447;,
  0.982531;-0.126563;-0.136436;,
  0.982584;-0.074127;0.170395;,
  0.013333;-0.945781;-0.324531;,
  0.013178;-0.905857;0.423378;,
  0.013537;0.992968;0.117607;,
  0.013537;0.992968;-0.117607;,
  -0.013543;0.992968;-0.117607;,
  -0.013543;0.992968;0.117607;,
  -0.013184;-0.905857;0.423378;,
  -0.013340;-0.945781;-0.324531;,
  0.003958;-0.439341;-0.898311;,
  1.000000;0.000046;0.000194;,
  0.000000;-0.000000;1.000000;,
  1.000000;-0.000058;0.000235;,
  -0.332810;0.915469;-0.226173;,
  0.008774;0.972298;-0.233580;,
  0.328301;0.916996;-0.226578;,
  -0.000001;0.000000;1.000000;,
  -1.000000;0.000028;-0.000113;,
  -0.008779;0.972298;-0.233580;,
  -0.003069;-0.341221;0.939978;,
  -0.003960;-0.439341;-0.898312;,
  -0.107103;0.986008;0.127738;,
  0.106098;0.986139;0.127569;,
  -0.985451;-0.108188;0.131081;,
  -0.340640;0.933231;-0.114211;,
  0.336092;0.934854;-0.114410;,
  1.000000;0.000076;0.000098;,
  1.000000;-0.000088;0.000139;,
  0.999383;-0.027789;-0.021464;,
  1.000000;-0.000101;-0.000139;,
  1.000000;-0.000071;-0.000223;,
  0.999381;-0.027819;-0.021548;,
  -1.000000;0.000038;-0.000068;,
  -1.000000;-0.000034;-0.000048;,
  -1.000000;-0.000022;-0.000094;,
  -1.000000;0.000043;0.000069;,
  -0.999832;0.014506;0.011197;,
  -0.999831;0.014517;0.011237;,
  -1.000000;0.000033;0.000108;,
  1.000000;-0.000002;0.000148;,
  1.000000;-0.000005;0.000296;,
  1.000000;-0.000002;-0.000153;,
  1.000000;-0.000004;-0.000307;,
  -1.000000;0.000001;-0.000073;,
  -1.000000;0.000002;-0.000145;,
  -1.000000;0.000001;0.000076;,
  -1.000000;0.000002;0.000152;,
  -0.986315;0.016702;0.164027;,
  0.985788;0.017021;0.167130;,
  -0.000000;1.000000;0.000703;,
  -0.000000;-0.549650;0.835395;,
  -0.000000;0.492724;0.870186;,
  -0.983161;-0.124313;-0.133945;,
  -0.949586;-0.246190;-0.194104;,
  -0.673710;0.734976;-0.076970;,
  -0.997465;0.000000;-0.071160;,
  0.947734;-0.250554;-0.197544;,
  0.997364;0.000000;-0.072555;,
  0.000066;0.911809;-0.410615;,
  0.000180;0.368972;-0.929441;,
  0.000220;0.031201;-0.999513;,
  0.000029;-0.983766;-0.179459;,
  0.000014;-0.995936;-0.090066;,
  0.000014;-0.996094;0.088296;,
  0.000028;-0.984418;0.175843;,
  0.000218;0.028965;0.999580;,
  0.000179;0.372290;0.928117;,
  0.000065;0.913749;0.406279;,
  0.000007;-0.995936;-0.090063;,
  0.000014;-0.983767;-0.179453;,
  0.000102;0.031199;-0.999513;,
  0.000085;0.368979;-0.929438;,
  0.000031;0.911812;-0.410608;,
  0.000031;0.913753;0.406271;,
  0.000085;0.372298;0.928113;,
  0.000104;0.028965;0.999580;,
  0.000013;-0.984419;0.175838;,
  0.000007;-0.996095;0.088293;,
  0.989337;0.071762;0.126737;,
  -0.120418;0.963545;0.238915;,
  -0.008778;0.972298;0.233580;,
  0.984884;-0.110258;0.133589;,
  0.003067;-0.341222;0.939978;,
  -0.989739;0.070404;0.124338;,
  0.122612;0.963285;0.238846;,
  0.008774;0.972298;0.233580;,
  -0.000001;0.492723;0.870186;,
  -0.000000;-0.549650;0.835395;,
  -0.000000;-0.549650;0.835395;,
  -0.000000;0.492724;0.870186;;
  78;
  4;0,0,0,0;,
  4;15,15,7,7;,
  4;30,10,20,19;,
  4;0,15,15,0;,
  4;21,24,11,31;,
  4;14,14,26,26;,
  4;0,26,26,0;,
  3;58,58,59;,
  4;46,46,45,45;,
  3;60,30,19;,
  4;61,58,58,60;,
  4;47,47,48,48;,
  3;3,21,31;,
  4;49,49,50,50;,
  3;5,62,5;,
  4;3,5,5,63;,
  4;52,52,51,51;,
  4;25,25,13,13;,
  3;29,1,1;,
  4;27,9,10,30;,
  4;60,2,27,30;,
  4;55,55,2,60;,
  4;31,28,4,3;,
  4;11,12,28,31;,
  4;49,49,51,51;,
  4;13,13,14,14;,
  4;7,8,8,7;,
  4;45,45,47,47;,
  4;32,32,16,16;,
  4;18,16,16,18;,
  4;18,18,33,33;,
  4;35,35,36,36;,
  4;36,37,37,36;,
  4;37,37,34,34;,
  4;33,35,35,33;,
  4;34,32,32,34;,
  4;38,38,23,23;,
  4;23,40,40,23;,
  4;40,40,39,39;,
  4;42,42,43,43;,
  4;44,43,43,44;,
  4;44,44,41,41;,
  4;39,42,42,39;,
  4;41,38,38,41;,
  4;64,64,65,65;,
  4;66,65,65,66;,
  4;67,67,68,68;,
  4;69,69,70,70;,
  4;71,72,72,71;,
  4;72,72,73,73;,
  4;68,69,69,68;,
  4;64,64,73,73;,
  4;74,74,75,75;,
  4;76,77,77,76;,
  4;77,77,78,78;,
  4;79,79,80,80;,
  4;81,80,80,81;,
  4;82,82,83,83;,
  4;78,79,79,78;,
  4;83,74,74,83;,
  4;3,4,55,55;,
  4;0,0,0,0;,
  4;22,25,25,22;,
  3;54,84,54;,
  3;28,85,4;,
  4;12,86,85,28;,
  3;6,6,87;,
  4;54,54,6,6;,
  4;17,88,88,17;,
  3;53,89,53;,
  4;90,91,9,27;,
  3;2,90,27;,
  4;57,57,92,2;,
  4;56,56,93,93;,
  4;94,56,56,94;,
  4;95,57,57,4;,
  4;53,1,1,53;,
  4;88,8,8,88;;
 }
 MeshTextureCoords {
  187;
  0.270724;0.658911;,
  0.270724;0.576637;,
  0.144901;0.576637;,
  0.144901;0.658911;,
  0.001374;0.736711;,
  0.112665;0.736711;,
  0.112685;0.663678;,
  0.001374;0.661661;,
  0.112685;0.419903;,
  0.001374;0.419903;,
  0.001394;0.491613;,
  0.112685;0.491613;,
  0.112665;0.816803;,
  0.001374;0.816803;,
  0.286531;0.491613;,
  0.397799;0.491613;,
  0.397789;0.419903;,
  0.286531;0.419903;,
  0.229773;0.661661;,
  0.118515;0.663678;,
  0.118506;0.736711;,
  0.229773;0.736711;,
  0.229773;0.816803;,
  0.118506;0.816803;,
  0.505430;0.536294;,
  0.577140;0.569412;,
  0.505430;0.494363;,
  0.988129;0.463404;,
  0.930671;0.465398;,
  0.867694;0.527352;,
  0.998626;0.527352;,
  0.117289;0.419903;,
  0.577140;0.649504;,
  0.505430;0.662117;,
  0.998602;0.861453;,
  0.867671;0.861453;,
  0.926849;0.920780;,
  0.988745;0.922774;,
  0.281837;0.419903;,
  0.753860;0.065222;,
  0.884791;0.065222;,
  0.821815;0.003263;,
  0.764357;0.001270;,
  0.500536;0.536294;,
  0.500536;0.494363;,
  0.428826;0.569412;,
  0.500536;0.662117;,
  0.428826;0.649504;,
  0.763741;0.460654;,
  0.825637;0.458661;,
  0.884815;0.399329;,
  0.753884;0.399329;,
  0.235442;0.742744;,
  0.346710;0.742744;,
  0.346700;0.666580;,
  0.235442;0.664564;,
  0.423932;0.494363;,
  0.352222;0.572543;,
  0.423932;0.536294;,
  0.112685;0.072980;,
  0.001374;0.072980;,
  0.117289;0.049739;,
  0.199563;0.419903;,
  0.199563;0.049739;,
  0.286531;0.072980;,
  0.281837;0.049739;,
  0.397789;0.072980;,
  0.809500;0.494363;,
  0.698241;0.494363;,
  0.698241;0.841286;,
  0.809500;0.841286;,
  0.693345;0.841286;,
  0.693345;0.494363;,
  0.582034;0.494363;,
  0.582034;0.841286;,
  0.403555;0.072980;,
  0.422727;0.079404;,
  0.485704;0.017447;,
  0.479719;0.001270;,
  0.556680;0.001270;,
  0.543161;0.015454;,
  0.553658;0.079404;,
  0.571177;0.072980;,
  0.571177;0.419903;,
  0.553634;0.413509;,
  0.543778;0.474833;,
  0.556680;0.491613;,
  0.481882;0.472840;,
  0.476588;0.491613;,
  0.422703;0.413509;,
  0.403555;0.419903;,
  0.578960;0.072980;,
  0.596478;0.079404;,
  0.606975;0.015454;,
  0.593457;0.001270;,
  0.664433;0.017447;,
  0.670418;0.001270;,
  0.727409;0.079404;,
  0.746582;0.072980;,
  0.746582;0.419903;,
  0.727433;0.413509;,
  0.668255;0.472840;,
  0.673549;0.491613;,
  0.593457;0.491613;,
  0.606359;0.474833;,
  0.596502;0.413509;,
  0.578960;0.419903;,
  0.490465;0.664867;,
  0.469331;0.664867;,
  0.469315;0.727844;,
  0.490449;0.727844;,
  0.490449;0.785302;,
  0.469315;0.785302;,
  0.940654;0.001270;,
  0.919520;0.001275;,
  0.919537;0.065223;,
  0.940671;0.065221;,
  0.940671;0.399326;,
  0.919537;0.399323;,
  0.919520;0.460644;,
  0.940654;0.460649;,
  0.545019;0.726764;,
  0.545019;0.664867;,
  0.523885;0.664867;,
  0.523885;0.726764;,
  0.814410;0.856840;,
  0.835544;0.856835;,
  0.835528;0.797507;,
  0.814394;0.797509;,
  0.835528;0.463406;,
  0.814394;0.463404;,
  0.892243;0.065223;,
  0.913377;0.065222;,
  0.913369;0.001270;,
  0.892235;0.001272;,
  0.517734;0.785302;,
  0.517734;0.727844;,
  0.496600;0.727844;,
  0.496600;0.785302;,
  0.517742;0.664867;,
  0.496608;0.664867;,
  0.861572;0.797511;,
  0.840438;0.797512;,
  0.840446;0.856843;,
  0.861580;0.856841;,
  0.572305;0.726764;,
  0.572305;0.664867;,
  0.551171;0.664867;,
  0.551171;0.726764;,
  0.892235;0.460652;,
  0.913369;0.460654;,
  0.913377;0.399329;,
  0.892243;0.399328;,
  0.840438;0.463404;,
  0.861572;0.463405;,
  0.270724;0.494363;,
  0.144901;0.494363;,
  0.346710;0.819705;,
  0.235442;0.819705;,
  0.330561;0.611435;,
  0.298859;0.661814;,
  0.347328;0.649504;,
  0.286531;0.001270;,
  0.397799;0.001270;,
  0.275618;0.536294;,
  0.347328;0.572543;,
  0.275618;0.494363;,
  0.463690;0.820008;,
  0.463690;0.743047;,
  0.352399;0.743047;,
  0.352399;0.820008;,
  0.352222;0.649504;,
  0.400690;0.661814;,
  0.368988;0.611435;,
  0.112685;0.001270;,
  0.001394;0.001270;,
  0.140007;0.576637;,
  0.089628;0.576637;,
  0.089628;0.658911;,
  0.140007;0.658911;,
  0.014487;0.576637;,
  0.014487;0.658911;,
  0.014487;0.494363;,
  0.089628;0.494363;,
  0.140007;0.494363;,
  0.463690;0.664867;,
  0.352379;0.666884;;
 }
 MeshVertexColors {
  187;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;,
  108;1.000000;1.000000;1.000000;1.000000;,
  109;1.000000;1.000000;1.000000;1.000000;,
  110;1.000000;1.000000;1.000000;1.000000;,
  111;1.000000;1.000000;1.000000;1.000000;,
  112;1.000000;1.000000;1.000000;1.000000;,
  113;1.000000;1.000000;1.000000;1.000000;,
  114;1.000000;1.000000;1.000000;1.000000;,
  115;1.000000;1.000000;1.000000;1.000000;,
  116;1.000000;1.000000;1.000000;1.000000;,
  117;1.000000;1.000000;1.000000;1.000000;,
  118;1.000000;1.000000;1.000000;1.000000;,
  119;1.000000;1.000000;1.000000;1.000000;,
  120;1.000000;1.000000;1.000000;1.000000;,
  121;1.000000;1.000000;1.000000;1.000000;,
  122;1.000000;1.000000;1.000000;1.000000;,
  123;1.000000;1.000000;1.000000;1.000000;,
  124;1.000000;1.000000;1.000000;1.000000;,
  125;1.000000;1.000000;1.000000;1.000000;,
  126;1.000000;1.000000;1.000000;1.000000;,
  127;1.000000;1.000000;1.000000;1.000000;,
  128;1.000000;1.000000;1.000000;1.000000;,
  129;1.000000;1.000000;1.000000;1.000000;,
  130;1.000000;1.000000;1.000000;1.000000;,
  131;1.000000;1.000000;1.000000;1.000000;,
  132;1.000000;1.000000;1.000000;1.000000;,
  133;1.000000;1.000000;1.000000;1.000000;,
  134;1.000000;1.000000;1.000000;1.000000;,
  135;1.000000;1.000000;1.000000;1.000000;,
  136;1.000000;1.000000;1.000000;1.000000;,
  137;1.000000;1.000000;1.000000;1.000000;,
  138;1.000000;1.000000;1.000000;1.000000;,
  139;1.000000;1.000000;1.000000;1.000000;,
  140;1.000000;1.000000;1.000000;1.000000;,
  141;1.000000;1.000000;1.000000;1.000000;,
  142;1.000000;1.000000;1.000000;1.000000;,
  143;1.000000;1.000000;1.000000;1.000000;,
  144;1.000000;1.000000;1.000000;1.000000;,
  145;1.000000;1.000000;1.000000;1.000000;,
  146;1.000000;1.000000;1.000000;1.000000;,
  147;1.000000;1.000000;1.000000;1.000000;,
  148;1.000000;1.000000;1.000000;1.000000;,
  149;1.000000;1.000000;1.000000;1.000000;,
  150;1.000000;1.000000;1.000000;1.000000;,
  151;1.000000;1.000000;1.000000;1.000000;,
  152;1.000000;1.000000;1.000000;1.000000;,
  153;1.000000;1.000000;1.000000;1.000000;,
  154;1.000000;1.000000;1.000000;1.000000;,
  155;1.000000;1.000000;1.000000;1.000000;,
  156;1.000000;1.000000;1.000000;1.000000;,
  157;1.000000;1.000000;1.000000;1.000000;,
  158;1.000000;1.000000;1.000000;1.000000;,
  159;1.000000;1.000000;1.000000;1.000000;,
  160;1.000000;1.000000;1.000000;1.000000;,
  161;1.000000;1.000000;1.000000;1.000000;,
  162;1.000000;1.000000;1.000000;1.000000;,
  163;1.000000;1.000000;1.000000;1.000000;,
  164;1.000000;1.000000;1.000000;1.000000;,
  165;1.000000;1.000000;1.000000;1.000000;,
  166;1.000000;1.000000;1.000000;1.000000;,
  167;1.000000;1.000000;1.000000;1.000000;,
  168;1.000000;1.000000;1.000000;1.000000;,
  169;1.000000;1.000000;1.000000;1.000000;,
  170;1.000000;1.000000;1.000000;1.000000;,
  171;1.000000;1.000000;1.000000;1.000000;,
  172;1.000000;1.000000;1.000000;1.000000;,
  173;1.000000;1.000000;1.000000;1.000000;,
  174;1.000000;1.000000;1.000000;1.000000;,
  175;1.000000;1.000000;1.000000;1.000000;,
  176;1.000000;1.000000;1.000000;1.000000;,
  177;1.000000;1.000000;1.000000;1.000000;,
  178;1.000000;1.000000;1.000000;1.000000;,
  179;1.000000;1.000000;1.000000;1.000000;,
  180;1.000000;1.000000;1.000000;1.000000;,
  181;1.000000;1.000000;1.000000;1.000000;,
  182;1.000000;1.000000;1.000000;1.000000;,
  183;1.000000;1.000000;1.000000;1.000000;,
  184;1.000000;1.000000;1.000000;1.000000;,
  185;1.000000;1.000000;1.000000;1.000000;,
  186;1.000000;1.000000;1.000000;1.000000;;
 }
}