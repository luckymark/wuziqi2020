#ifndef REFRESHS_H
#define REFRESHS_H

void MainWindow::refresh()
{
    int i = 0;
    int j = 0;
    player = 1;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            a[i][j] = 0;
        }
    }
    this->update();
}
#endif // REFRESHS_H
