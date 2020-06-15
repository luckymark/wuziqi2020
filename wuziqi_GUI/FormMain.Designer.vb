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
        Me.BtnUndo = New System.Windows.Forms.Button()
        Me.BtnStart = New System.Windows.Forms.Button()
        Me.BtnGiveUp = New System.Windows.Forms.Button()
        Me.BtnTip = New System.Windows.Forms.Button()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.BtnStopEVE = New System.Windows.Forms.Button()
        Me.BtnPause = New System.Windows.Forms.Button()
        Me.GroupGlobalSetting = New System.Windows.Forms.GroupBox()
        Me.CheckBox1 = New System.Windows.Forms.CheckBox()
        Me.Panel3 = New System.Windows.Forms.Panel()
        Me.RdiModeEVE = New System.Windows.Forms.RadioButton()
        Me.RdiModePVE = New System.Windows.Forms.RadioButton()
        Me.RdiModePVP = New System.Windows.Forms.RadioButton()
        Me.GpBoxEVESet = New System.Windows.Forms.GroupBox()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.RadioButton5 = New System.Windows.Forms.RadioButton()
        Me.RadioButton4 = New System.Windows.Forms.RadioButton()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.TxtRobotNameB = New System.Windows.Forms.TextBox()
        Me.TxtRobotNameA = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.TextBox3 = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.TextBox5 = New System.Windows.Forms.TextBox()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.PanelChessBoard = New System.Windows.Forms.Panel()
        Me.GroupBox4 = New System.Windows.Forms.GroupBox()
        Me.GpBoxPVESet = New System.Windows.Forms.GroupBox()
        Me.Label11 = New System.Windows.Forms.Label()
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Panel2 = New System.Windows.Forms.Panel()
        Me.RadioButton9 = New System.Windows.Forms.RadioButton()
        Me.RadioButton8 = New System.Windows.Forms.RadioButton()
        Me.Panel1 = New System.Windows.Forms.Panel()
        Me.RadioButton7 = New System.Windows.Forms.RadioButton()
        Me.RadioButton6 = New System.Windows.Forms.RadioButton()
        Me.GpBoxPVPSet = New System.Windows.Forms.GroupBox()
        Me.BtnPVPExchangeColor = New System.Windows.Forms.Button()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.TxtPVPWhiteName = New System.Windows.Forms.TextBox()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.TxtPVPBlackName = New System.Windows.Forms.TextBox()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.GroupBox1.SuspendLayout()
        Me.GroupGlobalSetting.SuspendLayout()
        Me.Panel3.SuspendLayout()
        Me.GpBoxEVESet.SuspendLayout()
        Me.GroupBox4.SuspendLayout()
        Me.GpBoxPVESet.SuspendLayout()
        Me.Panel2.SuspendLayout()
        Me.Panel1.SuspendLayout()
        Me.GpBoxPVPSet.SuspendLayout()
        Me.SuspendLayout()
        '
        'BtnUndo
        '
        Me.BtnUndo.Enabled = False
        Me.BtnUndo.Location = New System.Drawing.Point(15, 64)
        Me.BtnUndo.Name = "BtnUndo"
        Me.BtnUndo.Size = New System.Drawing.Size(78, 28)
        Me.BtnUndo.TabIndex = 1
        Me.BtnUndo.Text = "悔棋"
        Me.BtnUndo.UseVisualStyleBackColor = True
        '
        'BtnStart
        '
        Me.BtnStart.Location = New System.Drawing.Point(99, 64)
        Me.BtnStart.Name = "BtnStart"
        Me.BtnStart.Size = New System.Drawing.Size(76, 28)
        Me.BtnStart.TabIndex = 1
        Me.BtnStart.Text = "开始"
        Me.BtnStart.UseVisualStyleBackColor = True
        '
        'BtnGiveUp
        '
        Me.BtnGiveUp.Enabled = False
        Me.BtnGiveUp.Location = New System.Drawing.Point(15, 30)
        Me.BtnGiveUp.Name = "BtnGiveUp"
        Me.BtnGiveUp.Size = New System.Drawing.Size(78, 28)
        Me.BtnGiveUp.TabIndex = 1
        Me.BtnGiveUp.Text = "认输"
        Me.BtnGiveUp.UseVisualStyleBackColor = True
        '
        'BtnTip
        '
        Me.BtnTip.Enabled = False
        Me.BtnTip.Location = New System.Drawing.Point(99, 30)
        Me.BtnTip.Name = "BtnTip"
        Me.BtnTip.Size = New System.Drawing.Size(76, 28)
        Me.BtnTip.TabIndex = 1
        Me.BtnTip.Text = "提示"
        Me.BtnTip.UseVisualStyleBackColor = True
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.BtnStart)
        Me.GroupBox1.Controls.Add(Me.BtnStopEVE)
        Me.GroupBox1.Controls.Add(Me.BtnPause)
        Me.GroupBox1.Controls.Add(Me.BtnTip)
        Me.GroupBox1.Controls.Add(Me.BtnGiveUp)
        Me.GroupBox1.Controls.Add(Me.BtnUndo)
        Me.GroupBox1.Location = New System.Drawing.Point(769, 613)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(269, 111)
        Me.GroupBox1.TabIndex = 2
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "玩家操作区"
        '
        'BtnStopEVE
        '
        Me.BtnStopEVE.Enabled = False
        Me.BtnStopEVE.Location = New System.Drawing.Point(181, 64)
        Me.BtnStopEVE.Name = "BtnStopEVE"
        Me.BtnStopEVE.Size = New System.Drawing.Size(76, 28)
        Me.BtnStopEVE.TabIndex = 1
        Me.BtnStopEVE.Text = "停止EVE"
        Me.BtnStopEVE.UseVisualStyleBackColor = True
        '
        'BtnPause
        '
        Me.BtnPause.Enabled = False
        Me.BtnPause.Location = New System.Drawing.Point(181, 30)
        Me.BtnPause.Name = "BtnPause"
        Me.BtnPause.Size = New System.Drawing.Size(76, 28)
        Me.BtnPause.TabIndex = 1
        Me.BtnPause.Text = "暂停"
        Me.BtnPause.UseVisualStyleBackColor = True
        '
        'GroupGlobalSetting
        '
        Me.GroupGlobalSetting.Controls.Add(Me.CheckBox1)
        Me.GroupGlobalSetting.Controls.Add(Me.Panel3)
        Me.GroupGlobalSetting.Location = New System.Drawing.Point(1066, 565)
        Me.GroupGlobalSetting.Name = "GroupGlobalSetting"
        Me.GroupGlobalSetting.Size = New System.Drawing.Size(225, 159)
        Me.GroupGlobalSetting.TabIndex = 3
        Me.GroupGlobalSetting.TabStop = False
        Me.GroupGlobalSetting.Text = "全局设置"
        '
        'CheckBox1
        '
        Me.CheckBox1.AutoSize = True
        Me.CheckBox1.Enabled = False
        Me.CheckBox1.Location = New System.Drawing.Point(26, 131)
        Me.CheckBox1.Name = "CheckBox1"
        Me.CheckBox1.Size = New System.Drawing.Size(96, 16)
        Me.CheckBox1.TabIndex = 3
        Me.CheckBox1.Text = "启用禁手规则"
        Me.CheckBox1.UseVisualStyleBackColor = True
        '
        'Panel3
        '
        Me.Panel3.Controls.Add(Me.RdiModeEVE)
        Me.Panel3.Controls.Add(Me.RdiModePVE)
        Me.Panel3.Controls.Add(Me.RdiModePVP)
        Me.Panel3.Location = New System.Drawing.Point(26, 20)
        Me.Panel3.Name = "Panel3"
        Me.Panel3.Size = New System.Drawing.Size(158, 97)
        Me.Panel3.TabIndex = 1
        '
        'RdiModeEVE
        '
        Me.RdiModeEVE.AutoSize = True
        Me.RdiModeEVE.Location = New System.Drawing.Point(10, 70)
        Me.RdiModeEVE.Name = "RdiModeEVE"
        Me.RdiModeEVE.Size = New System.Drawing.Size(143, 16)
        Me.RdiModeEVE.TabIndex = 0
        Me.RdiModeEVE.TabStop = True
        Me.RdiModeEVE.Text = "EVE（机器人-机器人）"
        Me.RdiModeEVE.UseVisualStyleBackColor = True
        '
        'RdiModePVE
        '
        Me.RdiModePVE.AutoSize = True
        Me.RdiModePVE.Location = New System.Drawing.Point(10, 39)
        Me.RdiModePVE.Name = "RdiModePVE"
        Me.RdiModePVE.Size = New System.Drawing.Size(131, 16)
        Me.RdiModePVE.TabIndex = 0
        Me.RdiModePVE.TabStop = True
        Me.RdiModePVE.Text = "PVE（玩家-机器人）"
        Me.RdiModePVE.UseVisualStyleBackColor = True
        '
        'RdiModePVP
        '
        Me.RdiModePVP.AutoSize = True
        Me.RdiModePVP.Checked = True
        Me.RdiModePVP.Location = New System.Drawing.Point(10, 8)
        Me.RdiModePVP.Name = "RdiModePVP"
        Me.RdiModePVP.Size = New System.Drawing.Size(119, 16)
        Me.RdiModePVP.TabIndex = 0
        Me.RdiModePVP.TabStop = True
        Me.RdiModePVP.Text = "PVP（玩家-玩家）"
        Me.RdiModePVP.UseVisualStyleBackColor = True
        '
        'GpBoxEVESet
        '
        Me.GpBoxEVESet.Controls.Add(Me.Label8)
        Me.GpBoxEVESet.Controls.Add(Me.RadioButton5)
        Me.GpBoxEVESet.Controls.Add(Me.RadioButton4)
        Me.GpBoxEVESet.Enabled = False
        Me.GpBoxEVESet.Location = New System.Drawing.Point(1066, 490)
        Me.GpBoxEVESet.Name = "GpBoxEVESet"
        Me.GpBoxEVESet.Size = New System.Drawing.Size(225, 69)
        Me.GpBoxEVESet.TabIndex = 4
        Me.GpBoxEVESet.TabStop = False
        Me.GpBoxEVESet.Text = "EVE设置"
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(12, 33)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(41, 12)
        Me.Label8.TabIndex = 5
        Me.Label8.Text = "执棋："
        '
        'RadioButton5
        '
        Me.RadioButton5.AutoSize = True
        Me.RadioButton5.Location = New System.Drawing.Point(153, 33)
        Me.RadioButton5.Name = "RadioButton5"
        Me.RadioButton5.Size = New System.Drawing.Size(53, 16)
        Me.RadioButton5.TabIndex = 2
        Me.RadioButton5.Text = "B执黑"
        Me.RadioButton5.UseVisualStyleBackColor = True
        '
        'RadioButton4
        '
        Me.RadioButton4.AutoSize = True
        Me.RadioButton4.Checked = True
        Me.RadioButton4.Location = New System.Drawing.Point(73, 33)
        Me.RadioButton4.Name = "RadioButton4"
        Me.RadioButton4.Size = New System.Drawing.Size(53, 16)
        Me.RadioButton4.TabIndex = 2
        Me.RadioButton4.TabStop = True
        Me.RadioButton4.Text = "A执黑"
        Me.RadioButton4.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(11, 30)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(71, 12)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "机器人A名称"
        '
        'TxtRobotNameB
        '
        Me.TxtRobotNameB.Location = New System.Drawing.Point(88, 67)
        Me.TxtRobotNameB.Name = "TxtRobotNameB"
        Me.TxtRobotNameB.Size = New System.Drawing.Size(127, 21)
        Me.TxtRobotNameB.TabIndex = 0
        Me.TxtRobotNameB.Text = "RobotB"
        '
        'TxtRobotNameA
        '
        Me.TxtRobotNameA.Location = New System.Drawing.Point(88, 27)
        Me.TxtRobotNameA.Name = "TxtRobotNameA"
        Me.TxtRobotNameA.Size = New System.Drawing.Size(127, 21)
        Me.TxtRobotNameA.TabIndex = 0
        Me.TxtRobotNameA.Text = "RobotA"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(11, 70)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(71, 12)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "机器人B名称"
        '
        'TextBox3
        '
        Me.TextBox3.Location = New System.Drawing.Point(74, 110)
        Me.TextBox3.Name = "TextBox3"
        Me.TextBox3.Size = New System.Drawing.Size(51, 21)
        Me.TextBox3.TabIndex = 0
        Me.TextBox3.Text = "0"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(10, 113)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(29, 12)
        Me.Label3.TabIndex = 1
        Me.Label3.Text = "难度"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(49, 113)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(23, 12)
        Me.Label5.TabIndex = 1
        Me.Label5.Text = "A："
        '
        'TextBox5
        '
        Me.TextBox5.Location = New System.Drawing.Point(163, 110)
        Me.TextBox5.Name = "TextBox5"
        Me.TextBox5.Size = New System.Drawing.Size(51, 21)
        Me.TextBox5.TabIndex = 0
        Me.TextBox5.Text = "0"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(131, 113)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(23, 12)
        Me.Label6.TabIndex = 1
        Me.Label6.Text = "B："
        '
        'PanelChessBoard
        '
        Me.PanelChessBoard.BackgroundImage = Global.wuziqi_GUI.My.Resources.chessboard.board
        Me.PanelChessBoard.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch
        Me.PanelChessBoard.Enabled = False
        Me.PanelChessBoard.Location = New System.Drawing.Point(49, 47)
        Me.PanelChessBoard.Name = "PanelChessBoard"
        Me.PanelChessBoard.Size = New System.Drawing.Size(687, 679)
        Me.PanelChessBoard.TabIndex = 0
        '
        'GroupBox4
        '
        Me.GroupBox4.Controls.Add(Me.Label2)
        Me.GroupBox4.Controls.Add(Me.Label6)
        Me.GroupBox4.Controls.Add(Me.TxtRobotNameA)
        Me.GroupBox4.Controls.Add(Me.Label5)
        Me.GroupBox4.Controls.Add(Me.TxtRobotNameB)
        Me.GroupBox4.Controls.Add(Me.Label3)
        Me.GroupBox4.Controls.Add(Me.TextBox3)
        Me.GroupBox4.Controls.Add(Me.Label1)
        Me.GroupBox4.Controls.Add(Me.TextBox5)
        Me.GroupBox4.Location = New System.Drawing.Point(1066, 38)
        Me.GroupBox4.Name = "GroupBox4"
        Me.GroupBox4.Size = New System.Drawing.Size(225, 150)
        Me.GroupBox4.TabIndex = 5
        Me.GroupBox4.TabStop = False
        Me.GroupBox4.Text = "机器人设置"
        '
        'GpBoxPVESet
        '
        Me.GpBoxPVESet.Controls.Add(Me.Label11)
        Me.GpBoxPVESet.Controls.Add(Me.TextBox1)
        Me.GpBoxPVESet.Controls.Add(Me.Label7)
        Me.GpBoxPVESet.Controls.Add(Me.Label4)
        Me.GpBoxPVESet.Controls.Add(Me.Panel2)
        Me.GpBoxPVESet.Controls.Add(Me.Panel1)
        Me.GpBoxPVESet.Enabled = False
        Me.GpBoxPVESet.Location = New System.Drawing.Point(1066, 330)
        Me.GpBoxPVESet.Name = "GpBoxPVESet"
        Me.GpBoxPVESet.Size = New System.Drawing.Size(225, 154)
        Me.GpBoxPVESet.TabIndex = 6
        Me.GpBoxPVESet.TabStop = False
        Me.GpBoxPVESet.Text = "PVE设置"
        '
        'Label11
        '
        Me.Label11.AutoSize = True
        Me.Label11.Location = New System.Drawing.Point(11, 26)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(53, 12)
        Me.Label11.TabIndex = 7
        Me.Label11.Text = "玩家姓名"
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(70, 23)
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.Size = New System.Drawing.Size(145, 21)
        Me.TextBox1.TabIndex = 6
        Me.TextBox1.Text = "张三"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(11, 107)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(41, 12)
        Me.Label7.TabIndex = 5
        Me.Label7.Text = "执棋："
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(11, 65)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(41, 12)
        Me.Label4.TabIndex = 5
        Me.Label4.Text = "对手："
        '
        'Panel2
        '
        Me.Panel2.Controls.Add(Me.RadioButton9)
        Me.Panel2.Controls.Add(Me.RadioButton8)
        Me.Panel2.Location = New System.Drawing.Point(46, 93)
        Me.Panel2.Name = "Panel2"
        Me.Panel2.Size = New System.Drawing.Size(173, 36)
        Me.Panel2.TabIndex = 4
        '
        'RadioButton9
        '
        Me.RadioButton9.AutoSize = True
        Me.RadioButton9.Location = New System.Drawing.Point(89, 12)
        Me.RadioButton9.Name = "RadioButton9"
        Me.RadioButton9.Size = New System.Drawing.Size(83, 16)
        Me.RadioButton9.TabIndex = 2
        Me.RadioButton9.Text = "机器人执黑"
        Me.RadioButton9.UseVisualStyleBackColor = True
        '
        'RadioButton8
        '
        Me.RadioButton8.AutoSize = True
        Me.RadioButton8.Checked = True
        Me.RadioButton8.Location = New System.Drawing.Point(15, 12)
        Me.RadioButton8.Name = "RadioButton8"
        Me.RadioButton8.Size = New System.Drawing.Size(71, 16)
        Me.RadioButton8.TabIndex = 2
        Me.RadioButton8.TabStop = True
        Me.RadioButton8.Text = "玩家执黑"
        Me.RadioButton8.UseVisualStyleBackColor = True
        '
        'Panel1
        '
        Me.Panel1.Controls.Add(Me.RadioButton7)
        Me.Panel1.Controls.Add(Me.RadioButton6)
        Me.Panel1.Location = New System.Drawing.Point(46, 54)
        Me.Panel1.Name = "Panel1"
        Me.Panel1.Size = New System.Drawing.Size(163, 33)
        Me.Panel1.TabIndex = 3
        '
        'RadioButton7
        '
        Me.RadioButton7.AutoSize = True
        Me.RadioButton7.Location = New System.Drawing.Point(89, 9)
        Me.RadioButton7.Name = "RadioButton7"
        Me.RadioButton7.Size = New System.Drawing.Size(65, 16)
        Me.RadioButton7.TabIndex = 2
        Me.RadioButton7.Text = "机器人B"
        Me.RadioButton7.UseVisualStyleBackColor = True
        '
        'RadioButton6
        '
        Me.RadioButton6.AutoSize = True
        Me.RadioButton6.Checked = True
        Me.RadioButton6.Location = New System.Drawing.Point(15, 9)
        Me.RadioButton6.Name = "RadioButton6"
        Me.RadioButton6.Size = New System.Drawing.Size(65, 16)
        Me.RadioButton6.TabIndex = 2
        Me.RadioButton6.TabStop = True
        Me.RadioButton6.Text = "机器人A"
        Me.RadioButton6.UseVisualStyleBackColor = True
        '
        'GpBoxPVPSet
        '
        Me.GpBoxPVPSet.Controls.Add(Me.BtnPVPExchangeColor)
        Me.GpBoxPVPSet.Controls.Add(Me.Label10)
        Me.GpBoxPVPSet.Controls.Add(Me.TxtPVPWhiteName)
        Me.GpBoxPVPSet.Controls.Add(Me.Label9)
        Me.GpBoxPVPSet.Controls.Add(Me.TxtPVPBlackName)
        Me.GpBoxPVPSet.Location = New System.Drawing.Point(1066, 194)
        Me.GpBoxPVPSet.Name = "GpBoxPVPSet"
        Me.GpBoxPVPSet.Size = New System.Drawing.Size(225, 130)
        Me.GpBoxPVPSet.TabIndex = 7
        Me.GpBoxPVPSet.TabStop = False
        Me.GpBoxPVPSet.Text = "PVP设置"
        '
        'BtnPVPExchangeColor
        '
        Me.BtnPVPExchangeColor.Location = New System.Drawing.Point(78, 91)
        Me.BtnPVPExchangeColor.Name = "BtnPVPExchangeColor"
        Me.BtnPVPExchangeColor.Size = New System.Drawing.Size(77, 23)
        Me.BtnPVPExchangeColor.TabIndex = 2
        Me.BtnPVPExchangeColor.Text = "交换颜色"
        Me.BtnPVPExchangeColor.UseVisualStyleBackColor = True
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.Location = New System.Drawing.Point(11, 61)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(77, 12)
        Me.Label10.TabIndex = 1
        Me.Label10.Text = "白棋玩家姓名"
        '
        'TxtPVPWhiteName
        '
        Me.TxtPVPWhiteName.Location = New System.Drawing.Point(94, 58)
        Me.TxtPVPWhiteName.Name = "TxtPVPWhiteName"
        Me.TxtPVPWhiteName.Size = New System.Drawing.Size(121, 21)
        Me.TxtPVPWhiteName.TabIndex = 0
        Me.TxtPVPWhiteName.Text = "罗老师"
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(11, 25)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(77, 12)
        Me.Label9.TabIndex = 1
        Me.Label9.Text = "黑棋玩家姓名"
        '
        'TxtPVPBlackName
        '
        Me.TxtPVPBlackName.Location = New System.Drawing.Point(94, 22)
        Me.TxtPVPBlackName.Name = "TxtPVPBlackName"
        Me.TxtPVPBlackName.Size = New System.Drawing.Size(121, 21)
        Me.TxtPVPBlackName.TabIndex = 0
        Me.TxtPVPBlackName.Text = "张三"
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(889, 250)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(87, 44)
        Me.Button1.TabIndex = 8
        Me.Button1.Text = "Button1"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'FormMain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(1318, 776)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.GpBoxPVPSet)
        Me.Controls.Add(Me.GpBoxPVESet)
        Me.Controls.Add(Me.GroupBox4)
        Me.Controls.Add(Me.GpBoxEVESet)
        Me.Controls.Add(Me.GroupGlobalSetting)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.PanelChessBoard)
        Me.MaximizeBox = False
        Me.Name = "FormMain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "五子棋"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupGlobalSetting.ResumeLayout(False)
        Me.GroupGlobalSetting.PerformLayout()
        Me.Panel3.ResumeLayout(False)
        Me.Panel3.PerformLayout()
        Me.GpBoxEVESet.ResumeLayout(False)
        Me.GpBoxEVESet.PerformLayout()
        Me.GroupBox4.ResumeLayout(False)
        Me.GroupBox4.PerformLayout()
        Me.GpBoxPVESet.ResumeLayout(False)
        Me.GpBoxPVESet.PerformLayout()
        Me.Panel2.ResumeLayout(False)
        Me.Panel2.PerformLayout()
        Me.Panel1.ResumeLayout(False)
        Me.Panel1.PerformLayout()
        Me.GpBoxPVPSet.ResumeLayout(False)
        Me.GpBoxPVPSet.PerformLayout()
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents PanelChessBoard As Panel
    Friend WithEvents BtnUndo As Button
    Friend WithEvents BtnStart As Button
    Friend WithEvents BtnGiveUp As Button
    Friend WithEvents BtnTip As Button
    Friend WithEvents GroupBox1 As GroupBox
    Friend WithEvents GroupGlobalSetting As GroupBox
    Friend WithEvents RdiModeEVE As RadioButton
    Friend WithEvents RdiModePVE As RadioButton
    Friend WithEvents RdiModePVP As RadioButton
    Friend WithEvents GpBoxEVESet As GroupBox
    Friend WithEvents Label1 As Label
    Friend WithEvents TxtRobotNameB As TextBox
    Friend WithEvents TxtRobotNameA As TextBox
    Friend WithEvents RadioButton5 As RadioButton
    Friend WithEvents RadioButton4 As RadioButton
    Friend WithEvents Label2 As Label
    Friend WithEvents Label6 As Label
    Friend WithEvents Label5 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents TextBox5 As TextBox
    Friend WithEvents TextBox3 As TextBox
    Friend WithEvents CheckBox1 As CheckBox
    Friend WithEvents GroupBox4 As GroupBox
    Friend WithEvents GpBoxPVESet As GroupBox
    Friend WithEvents BtnStopEVE As Button
    Friend WithEvents BtnPause As Button
    Friend WithEvents RadioButton9 As RadioButton
    Friend WithEvents RadioButton8 As RadioButton
    Friend WithEvents RadioButton7 As RadioButton
    Friend WithEvents RadioButton6 As RadioButton
    Friend WithEvents Panel1 As Panel
    Friend WithEvents Panel3 As Panel
    Friend WithEvents Panel2 As Panel
    Friend WithEvents Label8 As Label
    Friend WithEvents Label7 As Label
    Friend WithEvents Label4 As Label
    Friend WithEvents GpBoxPVPSet As GroupBox
    Friend WithEvents BtnPVPExchangeColor As Button
    Friend WithEvents Label10 As Label
    Friend WithEvents TxtPVPWhiteName As TextBox
    Friend WithEvents Label9 As Label
    Friend WithEvents TxtPVPBlackName As TextBox
    Friend WithEvents Label11 As Label
    Friend WithEvents TextBox1 As TextBox
    Friend WithEvents Button1 As Button
End Class
