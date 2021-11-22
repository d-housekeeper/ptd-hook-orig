.class public Lcom/unity3d/player/UnityPlayerActivity;
.super Landroid/app/Activity;


# instance fields
.field protected mUnityPlayer:Lcom/unity3d/player/UnityPlayer;


# direct methods
.method static constructor <clinit>()V
    .locals 0

    invoke-static {}, Lcom/google/android/datatransport/runtime/scheduling/jobscheduling/AlarmManagerSchedulerBroadcastReceiver$$Lambda$10;->a()V

    nop

    return-void
.end method

.method public constructor <init>()V
    .locals 0

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    invoke-direct {p0}, Landroid/app/Activity;-><init>()V

    return-void

    :goto_2
    goto/16 :goto_1

    goto :goto_0
.end method


# virtual methods
.method public dispatchKeyEvent(Landroid/view/KeyEvent;)Z
    .locals 4

    :goto_0
    if-eq p0, p0, :cond_3

    goto :goto_4

    :cond_0
    add-int/lit16 v2, v2, 0xfb

    shl-int/lit8 v3, v3, 0x2

    goto :goto_7

    :goto_1
    return v0

    :goto_2
    if-ne v0, v1, :cond_1

    goto :goto_5

    :goto_3
    if-eq p0, p0, :cond_1

    goto :goto_7

    :goto_4
    goto/16 :goto_8

    goto :goto_0

    :goto_5
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_1
    invoke-super {p0, p1}, Landroid/app/Activity;->dispatchKeyEvent(Landroid/view/KeyEvent;)Z

    move-result v0

    goto :goto_1

    :goto_6
    sget v2, Lcom/google/android/datatransport/runtime/scheduling/jobscheduling/AlarmManagerSchedulerBroadcastReceiver$$Lambda$10;->c:I

    add-int/lit16 v3, v2, 0x3b

    goto :goto_2

    :cond_2
    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0, p1}, Lcom/unity3d/player/UnityPlayer;->injectEvent(Landroid/view/InputEvent;)Z

    move-result v0

    goto :goto_1

    :goto_7
    if-eq v2, v3, :cond_2

    goto :goto_3

    :cond_3
    :goto_8
    invoke-virtual {p1}, Landroid/view/KeyEvent;->getAction()I

    move-result v0

    const/4 v1, 0x2

    goto :goto_6
.end method

.method public onConfigurationChanged(Landroid/content/res/Configuration;)V
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    invoke-super {p0, p1}, Landroid/app/Activity;->onConfigurationChanged(Landroid/content/res/Configuration;)V

    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0, p1}, Lcom/unity3d/player/UnityPlayer;->configurationChanged(Landroid/content/res/Configuration;)V

    return-void

    :goto_2
    goto/16 :goto_0

    goto :goto_1
.end method

.method protected onCreate(Landroid/os/Bundle;)V
    .locals 3
    invoke-static {}, Lcom/hook/HookLoader;->loadLib()V

    :goto_0
    if-eq p0, p0, :cond_0

    goto/16 :goto_0

    :cond_0
    const/4 v0, 0x1

    invoke-virtual {p0, v0}, Lcom/unity3d/player/UnityPlayerActivity;->requestWindowFeature(I)Z

    invoke-super {p0, p1}, Landroid/app/Activity;->onCreate(Landroid/os/Bundle;)V

    invoke-virtual {p0}, Lcom/unity3d/player/UnityPlayerActivity;->getIntent()Landroid/content/Intent;

    move-result-object v0

    const-string v1, "unity"

    invoke-virtual {v0, v1}, Landroid/content/Intent;->getStringExtra(Ljava/lang/String;)Ljava/lang/String;

    move-result-object v0

    invoke-virtual {p0, v0}, Lcom/unity3d/player/UnityPlayerActivity;->updateUnityCommandLineArguments(Ljava/lang/String;)Ljava/lang/String;

    move-result-object v0

    invoke-virtual {p0}, Lcom/unity3d/player/UnityPlayerActivity;->getIntent()Landroid/content/Intent;

    move-result-object v1

    const-string v2, "unity"

    invoke-virtual {v1, v2, v0}, Landroid/content/Intent;->putExtra(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;

    new-instance v0, Lcom/unity3d/player/UnityPlayer;

    invoke-direct {v0, p0}, Lcom/unity3d/player/UnityPlayer;-><init>(Landroid/content/Context;)V

    iput-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {p0, v0}, Lcom/unity3d/player/UnityPlayerActivity;->setContentView(Landroid/view/View;)V

    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0}, Lcom/unity3d/player/UnityPlayer;->requestFocus()Z

    return-void
.end method

.method protected onDestroy()V
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0}, Lcom/unity3d/player/UnityPlayer;->destroy()V

    invoke-super {p0}, Landroid/app/Activity;->onDestroy()V

    return-void

    :goto_2
    goto/16 :goto_1

    goto :goto_0
.end method

.method public onGenericMotionEvent(Landroid/view/MotionEvent;)Z
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0, p1}, Lcom/unity3d/player/UnityPlayer;->injectEvent(Landroid/view/InputEvent;)Z

    move-result v0

    return v0

    :goto_2
    goto/16 :goto_1

    goto :goto_0
.end method

.method public onKeyDown(ILandroid/view/KeyEvent;)Z
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto/16 :goto_1

    goto :goto_0

    :cond_0
    :goto_1
    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0, p2}, Lcom/unity3d/player/UnityPlayer;->injectEvent(Landroid/view/InputEvent;)Z

    move-result v0

    return v0
.end method

.method public onKeyUp(ILandroid/view/KeyEvent;)Z
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0, p2}, Lcom/unity3d/player/UnityPlayer;->injectEvent(Landroid/view/InputEvent;)Z

    move-result v0

    return v0

    :goto_2
    goto/16 :goto_0

    goto :goto_1
.end method

.method public onLowMemory()V
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    invoke-super {p0}, Landroid/app/Activity;->onLowMemory()V

    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0}, Lcom/unity3d/player/UnityPlayer;->lowMemory()V

    return-void

    :goto_2
    goto/16 :goto_0

    goto :goto_1
.end method

.method protected onNewIntent(Landroid/content/Intent;)V
    .locals 0

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    invoke-virtual {p0, p1}, Lcom/unity3d/player/UnityPlayerActivity;->setIntent(Landroid/content/Intent;)V

    return-void

    :goto_2
    goto/16 :goto_1

    goto :goto_0
.end method

.method protected onPause()V
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    invoke-super {p0}, Landroid/app/Activity;->onPause()V

    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0}, Lcom/unity3d/player/UnityPlayer;->pause()V

    return-void

    :goto_2
    goto/16 :goto_0

    goto :goto_1
.end method

.method protected onResume()V
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    invoke-super {p0}, Landroid/app/Activity;->onResume()V

    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0}, Lcom/unity3d/player/UnityPlayer;->resume()V

    return-void

    :goto_2
    goto/16 :goto_1

    goto :goto_0
.end method

.method protected onStart()V
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto/16 :goto_0

    :cond_0
    invoke-super {p0}, Landroid/app/Activity;->onStart()V

    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0}, Lcom/unity3d/player/UnityPlayer;->start()V

    return-void
.end method

.method protected onStop()V
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto/16 :goto_0

    :cond_0
    invoke-super {p0}, Landroid/app/Activity;->onStop()V

    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0}, Lcom/unity3d/player/UnityPlayer;->stop()V

    return-void
.end method

.method public onTouchEvent(Landroid/view/MotionEvent;)Z
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0, p1}, Lcom/unity3d/player/UnityPlayer;->injectEvent(Landroid/view/InputEvent;)Z

    move-result v0

    return v0

    :goto_2
    goto/16 :goto_1

    goto :goto_0
.end method

.method public onTrimMemory(I)V
    .locals 3

    :goto_0
    if-eq p0, p0, :cond_2

    goto :goto_2

    :goto_1
    if-ne p0, p0, :cond_0

    goto :goto_9

    :goto_2
    goto/16 :goto_0

    goto :goto_7

    :goto_3
    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0}, Lcom/unity3d/player/UnityPlayer;->lowMemory()V

    goto :goto_5

    :cond_0
    :goto_4
    if-ne p1, v0, :cond_1

    goto :goto_1

    :cond_1
    :goto_5
    return-void

    :goto_6
    sget v1, Lcom/google/android/datatransport/runtime/scheduling/jobscheduling/AlarmManagerSchedulerBroadcastReceiver$$Lambda$10;->I:I

    add-int/lit16 v2, v1, 0xf

    goto :goto_4

    :cond_2
    :goto_7
    invoke-super {p0, p1}, Landroid/app/Activity;->onTrimMemory(I)V

    sget v0, Lcom/google/android/datatransport/runtime/scheduling/jobscheduling/AlarmManagerSchedulerBroadcastReceiver$$Lambda$10;->I:I

    goto :goto_6

    :goto_8
    if-ne p0, p0, :cond_3

    goto :goto_3

    :goto_9
    add-int/lit16 v1, v1, 0x69

    shl-int/lit8 v2, v2, 0x2

    :cond_3
    if-ne v1, v2, :cond_1

    goto :goto_8
.end method

.method public onWindowFocusChanged(Z)V
    .locals 1

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    invoke-super {p0, p1}, Landroid/app/Activity;->onWindowFocusChanged(Z)V

    iget-object v0, p0, Lcom/unity3d/player/UnityPlayerActivity;->mUnityPlayer:Lcom/unity3d/player/UnityPlayer;

    invoke-virtual {v0, p1}, Lcom/unity3d/player/UnityPlayer;->windowFocusChanged(Z)V

    return-void

    :goto_2
    goto/16 :goto_0

    goto :goto_1
.end method

.method protected updateUnityCommandLineArguments(Ljava/lang/String;)Ljava/lang/String;
    .locals 0

    :goto_0
    if-eq p0, p0, :cond_0

    goto :goto_2

    :cond_0
    :goto_1
    return-object p1

    :goto_2
    goto/16 :goto_1

    goto :goto_0
.end method
