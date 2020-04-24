<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class FormMain
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。  
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.PanelChessBoard = New System.Windows.Forms.Panel()
        Me.SuspendLayout()
        '
        'PanelChessBoard
        '
        Me.PanelChessBoard.BackgroundImage = Global.wuziqi_GUI.My.Resources.chessboard.board
        Me.PanelChessBoard.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch
        Me.PanelChessBoard.Location = New System.Drawing.Point(49, 47)
        Me.PanelChessBoard.Name = "PanelChessBoard"
        Me.PanelChessBoard.Size = New System.Drawing.Size(687, 679)
        Me.PanelChessBoard.TabIndex = 0
        '
        'FormMain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.Color.LightGray
        Me.ClientSize = New System.Drawing.Size(1127, 776)
        Me.Controls.Add(Me.PanelChessBoard)
        Me.MaximizeBox = False
        Me.Name = "FormMain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "五子棋"
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents PanelChessBoard As Panel
End Class
