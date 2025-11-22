class BSHC_Helper 
{
    private static ref BSHC_Helper instance;

    static BSHC_Helper GetInstance()
    {
        if (!instance)
        {
            instance = new BSHC_Helper();
        }
        return instance;
    }

    static void BSHC_PlaySoundOnObject(string soundSet, Object parentObject) 
    {
        if (!parentObject) return; 

        EffectSound soundEffect = SEffectManager.PlaySoundOnObject(soundSet, parentObject);

        if (soundEffect) {
             soundEffect.SetSoundAutodestroy(true);
        } else {

        }
    }
    private void BSHC_Helper() {}
    private void ~BSHC_Helper() {}

} 
