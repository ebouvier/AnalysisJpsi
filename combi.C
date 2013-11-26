int combi(double mt1 = 173., double dmt1 = 1., 
             double mt2 = 173., double dmt2 = 1.) {
  double dmt = pow((pow(dmt1,-2.)+pow(dmt2,-2.)),-0.5);
  double mt = (pow(dmt1,-2.)*mt1+pow(dmt2,-2.)*mt2)/(pow(dmt1,-2.)+pow(dmt2,-2.));
  TString result = TString::Format("Apres combinaison des canaux muonique et electronique : \n \t \t \t m_{t} = (%3.1f #pm %3.1f) GeV/c^{2}", mt, dmt);
  cout << result << endl;
  return 0;
}
